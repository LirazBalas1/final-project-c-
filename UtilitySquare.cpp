//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "UtilitySquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

UtilitySquare::UtilitySquare(const std::string& name, int cost)
    : Square(name), cost(cost), owner(nullptr) {}

int UtilitySquare::getCost() const {
    return cost;
}

int UtilitySquare::calculateRent(int diceRoll) const {
    if (owner == nullptr) return 0;
    int multiplier = (owner->getNumberOfUtilities() == 1) ? 4 : 10;
    return diceRoll * multiplier;
}

void UtilitySquare::buyProperty(Player* player, sf::RenderWindow& window) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->setBalance(player->getBalance() - cost);
        setOwner(player);
        // Additional logic for buying utility
    }
}

void UtilitySquare::action(Player* player, Board* board, sf::RenderWindow& window) {
    if (owner == nullptr) {
        // Offer to buy utility
        buyProperty(player, window);
    } else if (owner != player) {
        // Pay rent based on dice roll
        int diceRoll = player->rollDice();
        int rent = calculateRent(diceRoll);
        player->payRent(rent, owner, window);
    }
}

void UtilitySquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(sf::Color(200, 200, 200));  // Light gray for utilities
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.0f);
    window.draw(square);

    sf::Text nameText(name, font, 10);
    nameText.setPosition(position.x + 5, position.y + 5);
    nameText.setFillColor(sf::Color::Black);
    window.draw(nameText);

    sf::Text costText("$" + std::to_string(cost), font, 10);
    costText.setPosition(position.x + 5, position.y + size - 20);
    costText.setFillColor(sf::Color::Black);
    window.draw(costText);

    if (owner) {
        sf::CircleShape ownerToken(5);
        ownerToken.setFillColor(owner->getColor());
        ownerToken.setPosition(position.x + size - 15, position.y + 5);
        window.draw(ownerToken);
    }
}

UtilitySquare::~UtilitySquare() {}