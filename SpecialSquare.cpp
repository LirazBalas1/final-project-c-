//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "SpecialSquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

SpecialSquare::SpecialSquare(const std::string& name) : Square(name) {}

void SpecialSquare::action(Player* player, Board* board, sf::RenderWindow& window) {
    if (name == "Go") {
        std::cout << player->getName() << " landed on Go!" << std::endl;
        player->addMoney(200, window);
    } else if (name == "Income Tax") {
        std::cout << player->getName() << " must pay Income Tax!" << std::endl;
        player->payRent(200, nullptr, window);  // Pay to bank
    } else if (name == "Luxury Tax") {
        std::cout << player->getName() << " must pay Luxury Tax!" << std::endl;
        player->payRent(75, nullptr, window);  // Pay to bank
    } else if (name == "Go to Jail") {
        std::cout << player->getName() << " is going to Jail!" << std::endl;
        player->sendToJail(window);
    } else if (name == "Free Parking") {
        std::cout << player->getName() << " is relaxing on Free Parking!" << std::endl;
    } else if (name == "Jail") {
        std::cout << player->getName() << " is just visiting Jail." << std::endl;
    }
}

void SpecialSquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(sf::Color::White);
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.0f);
    window.draw(square);

    sf::Text nameText(name, font, 12);
    nameText.setPosition(position.x + 5, position.y + size / 2 - 10);
    nameText.setFillColor(sf::Color::Black);
    window.draw(nameText);

    if (name == "Go") {
        sf::Text goText("Collect $200", font, 10);
        goText.setPosition(position.x + 5, position.y + size - 20);
        goText.setFillColor(sf::Color::Black);
        window.draw(goText);
    } else if (name == "Income Tax" || name == "Luxury Tax") {
        sf::Text taxText(name == "Income Tax" ? "Pay $200" : "Pay $75", font, 10);
        taxText.setPosition(position.x + 5, position.y + size - 20);
        taxText.setFillColor(sf::Color::Black);
        window.draw(taxText);
    }
}

SpecialSquare::~SpecialSquare() {}