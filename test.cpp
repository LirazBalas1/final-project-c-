//Liraz Balas
//211801220
//lbalad13@gmail.com
// Main test setup with Doctest configuration
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Player.hpp"
#include "Board.hpp"
#include "Dice.hpp"
#include "Card.hpp"
#include "GameController.hpp"
#include "PropertySquare.hpp"
#include "StreetSquare.hpp"
#include "RailroadSquare.hpp"
#include "UtilitySquare.hpp"
#include "SpecialSquare.hpp"
#include "ChanceSquare.hpp"
#include "CommunityChestSquare.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

TEST_CASE("Test initial player balance and position") {
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition
    CHECK(player1.getBalance() == 1500);
    CHECK(player1.getPosition() == 0);
}

TEST_CASE("Test player movement across the board") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition

    // Move player by 5 spaces
    player1.move(5, board);
    CHECK(player1.getPosition() == 5);

    // Move player around the board (exceeding 40 spaces)
    player1.move(36, board); // Total move would be 41, wraparound to position 1
    CHECK(player1.getPosition() == 1);
}

TEST_CASE("Test dice rolling") {
    Dice dice;
    for (int i = 0; i < 100; ++i) {
        int total = dice.roll();
        CHECK(total >= 2);
        CHECK(total <= 12);
    }
}

TEST_CASE("Test buying properties and rent") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition
    Player player2("Player 2", 1500, sf::Color::Blue, false);  // Removed startPosition

    // Player 1 buys a property
    PropertySquare* property = dynamic_cast<PropertySquare*>(board.getSquareAtPosition(1));  // Mediterranean Avenue
    REQUIRE(property != nullptr);  // Add this check

    // Simulate buying the property
    player1.buyProperty(property);

    CHECK(player1.getBalance() == 1440);  // Property cost 60
    CHECK(property->getOwner() == &player1);

    // Player 2 lands on Player 1's property and pays rent
    player2.setPosition(1);
    int initialBalance = player2.getBalance();
    property->action(&player2, &board);
    CHECK(player2.getBalance() < initialBalance);  // Should have paid rent
    CHECK(player1.getBalance() > 1440);  // Should have received rent
}

TEST_CASE("Test player interaction with utilities") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition
    Player player2("Player 2", 1500, sf::Color::Blue, false);  // Removed startPosition

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Player 1 buys Electric Company
    Square* electricCompanySquare = board.getSquareAtPosition(12);  // Electric Company
    UtilitySquare* electricCompany = dynamic_cast<UtilitySquare*>(electricCompanySquare);
    CHECK(electricCompany != nullptr); 
    player1.buyProperty(electricCompany);
    CHECK(player1.getBalance() == 1350);  // Paid $150 for Electric Company

    // Player 2 lands on Electric Company
    player2.setPosition(12);
    int rent = electricCompany->calculateRent(6);  // Assume dice roll of 6 for rent calculation
    player2.payRent(rent, &player1);
    CHECK(player2.getBalance() == 1440);  // Paid rent based on utility rules
    CHECK(player1.getBalance() == 1410);  // Player 1 received rent
}

TEST_CASE("Test edge cases: player bankruptcy") {
    Board board;
    Player player1("Player 1", 50, sf::Color::Red, false);  // Removed startPosition
    Player player2("Player 2", 1500, sf::Color::Blue, false);  // Removed startPosition

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Player 2 owns a property, player 1 lands on it and goes bankrupt
    Square* square = board.getSquareAtPosition(1);  // Mediterranean Avenue
    PropertySquare* property = dynamic_cast<PropertySquare*>(square);
    player2.buyProperty(property);

    player1.setPosition(1);
    property->action(&player1, &board);
    CHECK(player1.isBankrupt() == true);
}

TEST_CASE("Test player goes to jail and pays to get out") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Simulate landing on "Go to Jail"
    player1.setPosition(30);  // Go to Jail position
    Square* goToJailSquare = board.getSquareAtPosition(30);
    CHECK(goToJailSquare != nullptr);

    // Player is sent to jail
    goToJailSquare->action(&player1, &board);
    CHECK(player1.isInJail() == true);

    // Player pays to get out of jail
    player1.addMoney(-50);  // Deduct money for release
    player1.getOutOfJail();
    CHECK(player1.isInJail() == false);  // Player is out of jail
    CHECK(player1.getBalance() == 1450);  // Balance after paying fine
}

TEST_CASE("Test special squares handling") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Simulate landing on "Go" and collecting $200
    player1.setPosition(0);  // Go square
    Square* goSquare = board.getSquareAtPosition(0);
    CHECK(goSquare != nullptr);
    goSquare->action(&player1, &board);
    CHECK(player1.getBalance() == 1700);  // Player should collect $200 for landing on Go

    // Simulate landing on "Income Tax"
    player1.setPosition(4);  // Income Tax square
    Square* incomeTaxSquare = board.getSquareAtPosition(4);
    CHECK(incomeTaxSquare != nullptr);
    incomeTaxSquare->action(&player1, &board);
    CHECK(player1.getBalance() == 1500);  // Player should pay $200 for Income Tax

    // Simulate landing on "Go to Jail"
    player1.setPosition(30);  // Go to Jail square
    Square* goToJailSquare = board.getSquareAtPosition(30);
    CHECK(goToJailSquare != nullptr);
    goToJailSquare->action(&player1, &board);
    CHECK(player1.isInJail() == true);  // Player should be in Jail
    CHECK(player1.getPosition() == 10);  // Jail position
}

TEST_CASE("Test player interaction with railroads") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition
    Player player2("Player 2", 1500, sf::Color::Blue, false);  // Removed startPosition

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Player 1 buys Reading Railroad
    Square* readingRailroadSquare = board.getSquareAtPosition(5);  // Reading Railroad
    RailroadSquare* readingRailroad = dynamic_cast<RailroadSquare*>(readingRailroadSquare);
    CHECK(readingRailroad != nullptr); 
    player1.buyProperty(readingRailroad);
    CHECK(player1.getBalance() == 1300);  // Paid $200 for Reading Railroad

    // Player 2 lands on Reading Railroad
    player2.setPosition(5);
    int rent = readingRailroad->calculateRent();  // Rent should be $25 for 1 railroad
    player2.payRent(rent, &player1);
    CHECK(player2.getBalance() == 1475);  // Paid $25 rent
    CHECK(player1.getBalance() == 1325);  // Player 1 received $25 rent
}

TEST_CASE("Test full player turn and interaction with properties and rent") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red, false);  // Removed startPosition
    Player player2("Player 2", 1500, sf::Color::Blue, false);  // Removed startPosition

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Simulate full player 1 turn
    player1.move(5, board); // Move to property square (position 5)
    Square* landedSquare = board.getSquareAtPosition(player1.getPosition());
    PropertySquare* property = dynamic_cast<PropertySquare*>(landedSquare);

    REQUIRE(property != nullptr); // Ensure player landed on a buyable property

    // Player 1 buys the property
    player1.buyProperty(property);
    CHECK(player1.getBalance() == 1300);  // Balance after purchasing property

    // Player 2 lands on player 1's property and pays rent
    player2.move(5, board);
    property->action(&player2, &board);

    // Check balances after rent payment
    CHECK(player2.getBalance() < 1500);  // Player 2 paid rent
    CHECK(player1.getBalance() > 1300);  // Player 1 received rent
}
