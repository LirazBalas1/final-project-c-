//Liraz Balas
//211801220
//lbalad13@gmail.com
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
    Player player1("Player 1", 1500, sf::Color::Red);
    CHECK(player1.getBalance() == 1500);
    CHECK(player1.getPosition() == 0);
}

TEST_CASE("Test player movement across the board") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Move player by 5 spaces
    player1.move(5, board, window);
    CHECK(player1.getPosition() == 5);

    // Move player around the board (exceeding 40 spaces)
    player1.move(36, board, window); // Total move would be 41, wraparound to position 1
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
    Player player1("Player 1", 1500, sf::Color::Red);
    Player player2("Player 2", 1500, sf::Color::Blue);
    
    sf::RenderWindow window;

    // Player 1 buys a property
    Square* square = board.getSquareAtPosition(1);  // Mediterranean Avenue
    REQUIRE(square != nullptr);  // Add this check
    PropertySquare* property = dynamic_cast<PropertySquare*>(square);
    REQUIRE(property != nullptr);
    
    // Simulate buying the property
    player1.buyProperty(property, window);

    CHECK(player1.getBalance() == 1440);  // Property cost 60
    CHECK(property->getOwner() == &player1);

    // Player 2 lands on Player 1's property and pays rent
    player2.setPosition(1);
    int initialBalance = player2.getBalance();
    property->action(&player2, &board, window);
    CHECK(player2.getBalance() < initialBalance);  // Should have paid rent
    CHECK(player1.getBalance() > 1440);  // Should have received rent
}

TEST_CASE("Test edge cases: player bankruptcy") {
    Board board;
    Player player1("Player 1", 50, sf::Color::Red);
    Player player2("Player 2", 1500, sf::Color::Blue);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Player 2 owns a property, player 1 lands on it and goes bankrupt
    Square* square = board.getSquareAtPosition(1);  // Mediterranean Avenue
    PropertySquare* property = dynamic_cast<PropertySquare*>(square);
    player2.buyProperty(property, window);

    player1.setPosition(1);
    player1.payRent(property->calculateRent(), &player2, window);
    CHECK(player1.isBankrupt() == true);
}

TEST_CASE("Test player interaction with utilities") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red);
    Player player2("Player 2", 1500, sf::Color::Blue);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");
    
    // Player 1 buys Electric Company
    Square* electricCompanySquare = board.getSquareAtPosition(12);  // Electric Company
    UtilitySquare* electricCompany = dynamic_cast<UtilitySquare*>(electricCompanySquare);
    CHECK(electricCompany != nullptr); 
    player1.buyProperty(electricCompany, window);
    CHECK(player1.getBalance() == 1350);  // Paid $150 for Electric Company

    // Player 2 lands on Electric Company
    player2.setPosition(12);
    int rent = electricCompany->calculateRent(6);  // Assume dice roll of 6 for rent calculation
    player2.payRent(rent, &player1, window);  
    CHECK(player2.getBalance() == 1440);  // Paid rent based on utility rules
    CHECK(player1.getBalance() == 1410);  // Player 1 received rent
}

TEST_CASE("Test player bankrupt after landing on expensive property") {
    Board board;
    Player player1("Player 1", 150, sf::Color::Red);  // Player with limited money
    Player player2("Player 2", 1500, sf::Color::Blue);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");
    
    // Player 2 owns Boardwalk
    Square* boardwalkSquare = board.getSquareAtPosition(39);  // Boardwalk
    PropertySquare* boardwalk = dynamic_cast<PropertySquare*>(boardwalkSquare);
    CHECK(boardwalk != nullptr);
    player2.buyProperty(boardwalk, window);

    // Player 1 lands on Boardwalk
    player1.setPosition(39);
    int rent = boardwalk->calculateRent();
    player1.payRent(rent, &player2, window);  // Player 1 pays rent

    CHECK(player1.isBankrupt() == true);  // Player 1 should be bankrupt
    CHECK(player2.getBalance() > 1500);   // Player 2 receives rent
}
TEST_CASE("Test special squares handling") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Simulate landing on "Go" and collecting $200
    player1.setPosition(0);  // Go square
    Square* goSquare = board.getSquareAtPosition(0);
    CHECK(goSquare != nullptr);
    goSquare->action(&player1, &board, window);
    CHECK(player1.getBalance() == 1700);  // Player should collect $200 for landing on Go

    // Simulate landing on "Income Tax"
    player1.setPosition(4);  // Income Tax square
    Square* incomeTaxSquare = board.getSquareAtPosition(4);
    CHECK(incomeTaxSquare != nullptr);
    incomeTaxSquare->action(&player1, &board, window);
    CHECK(player1.getBalance() == 1500);  // Player should pay $200 for Income Tax

    // Simulate landing on "Go to Jail"
    player1.setPosition(30);  // Go to Jail square
    Square* goToJailSquare = board.getSquareAtPosition(30);
    CHECK(goToJailSquare != nullptr);
    goToJailSquare->action(&player1, &board, window);
    CHECK(player1.isInJail() == true);  // Player should be in Jail
    CHECK(player1.getPosition() == 10);  // Jail position
}

TEST_CASE("Test player interaction with railroads") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red);
    Player player2("Player 2", 1500, sf::Color::Blue);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");
    
    // Player 1 buys Reading Railroad
    Square* readingRailroadSquare = board.getSquareAtPosition(5);  // Reading Railroad
    RailroadSquare* readingRailroad = dynamic_cast<RailroadSquare*>(readingRailroadSquare);
    CHECK(readingRailroad != nullptr); 
    player1.buyProperty(readingRailroad, window);
    CHECK(player1.getBalance() == 1300);  // Paid $200 for Reading Railroad

    // Player 2 lands on Reading Railroad
    player2.setPosition(5);
    int rent = readingRailroad->calculateRent();  // Rent should be $25 for 1 railroad
    player2.payRent(rent, &player1, window);  
    CHECK(player2.getBalance() == 1475);  // Paid $25 rent
    CHECK(player1.getBalance() == 1325);  // Player 1 received $25 rent
}

TEST_CASE("Test player buying street properties") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Player 1 buys Mediterranean Avenue
    Square* mediterraneanAvenueSquare = board.getSquareAtPosition(1);  // Mediterranean Avenue
    StreetSquare* mediterraneanAvenue = dynamic_cast<StreetSquare*>(mediterraneanAvenueSquare);
    CHECK(mediterraneanAvenue != nullptr);
    player1.buyProperty(mediterraneanAvenue, window);
    CHECK(player1.getBalance() == 1440);  // Paid $60 for Mediterranean Avenue
    CHECK(mediterraneanAvenue->getOwner() == &player1);  // Player 1 is the owner
}

TEST_CASE("Test street property rent calculation") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red);
    Player player2("Player 2", 1500, sf::Color::Blue);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Player 1 buys Baltic Avenue
    Square* balticAvenueSquare = board.getSquareAtPosition(3);  // Baltic Avenue
    StreetSquare* balticAvenue = dynamic_cast<StreetSquare*>(balticAvenueSquare);
    CHECK(balticAvenue != nullptr);
    player1.buyProperty(balticAvenue, window);

    // Player 2 lands on Baltic Avenue
    player2.setPosition(3);
    int rent = balticAvenue->calculateRent();  // Rent should be $4 for Baltic Avenue
    player2.payRent(rent, &player1, window);  
    CHECK(player2.getBalance() == 1496);  // Paid $4 rent
    CHECK(player1.getBalance() == 1504);  // Player 1 received $4 rent
}

TEST_CASE("Test getting properties by color group") {
    Board board;

    // Get brown properties
    std::vector<Square*> brownProperties = board.getPropertiesByColor(sf::Color(150, 75, 0));
    CHECK(brownProperties.size() == 2);  // There should be 2 brown properties
    CHECK(brownProperties[0]->getName() == "Mediterranean Avenue");
    CHECK(brownProperties[1]->getName() == "Baltic Avenue");

    // Get dark blue properties
    std::vector<Square*> darkBlueProperties = board.getPropertiesByColor(sf::Color(0, 0, 255));
    CHECK(darkBlueProperties.size() == 2);  // There should be 2 dark blue properties
    CHECK(darkBlueProperties[0]->getName() == "Park Place");
    CHECK(darkBlueProperties[1]->getName() == "Boardwalk");
}

TEST_CASE("Test landing on Chance and Community Chest squares") {
    Board board;
    Player player1("Player 1", 1500, sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly Test");

    // Simulate landing on a Chance square
    player1.setPosition(7);  // Chance square
    Square* chanceSquare = board.getSquareAtPosition(7);
    CHECK(chanceSquare != nullptr);
    chanceSquare->action(&player1, &board, window);

    // Simulate landing on a Community Chest square
    player1.setPosition(17);  // Community Chest square
    Square* communityChestSquare = board.getSquareAtPosition(17);
    CHECK(communityChestSquare != nullptr);
    communityChestSquare->action(&player1, &board, window);
}

TEST_CASE("Test dice rolling and doubles counting") {
    Dice dice;

    // Roll the dice multiple times
    for (int i = 0; i < 100; ++i) {
        int total = dice.roll();
        CHECK(total >= 2);
        CHECK(total <= 12);

        // Check if doubles are counted correctly
        if (dice.isDouble()) {
            CHECK(dice.getDoublesCount() == i + 1);
        } else {
            CHECK(dice.getDoublesCount() == 0);
        }
    }

    // Reset doubles count
    dice.resetDoublesCount();
    CHECK(dice.getDoublesCount() == 0);
}
TEST_CASE("Test getting properties by color group") {
    Board board;

    // Get brown properties
    std::vector<Square*> brownProperties = board.getPropertiesByColor(sf::Color(150, 75, 0));
    CHECK(brownProperties.size() == 2);  // There should be 2 brown properties
    CHECK(brownProperties[0]->getName() == "Mediterranean Avenue");
    CHECK(brownProperties[1]->getName() == "Baltic Avenue");

    // Get dark blue properties
    std::vector<Square*> darkBlueProperties = board.getPropertiesByColor(sf::Color(0, 0, 255));
    CHECK(darkBlueProperties.size() == 2);  // There should be 2 dark blue properties
    CHECK(darkBlueProperties[0]->getName() == "Park Place");
    CHECK(darkBlueProperties[1]->getName() == "Boardwalk");
}