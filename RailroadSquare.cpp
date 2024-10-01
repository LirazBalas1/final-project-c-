//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "RailroadSquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

RailroadSquare::RailroadSquare(const std::string& name, int cost)
    : Square(name), cost(cost), baseRent(25), owner(nullptr) {}

int RailroadSquare::getCost() const {
    return cost;
}

int RailroadSquare::calculateRent() const {
    if (owner == nullptr) return 0;
    return baseRent * (1 << (owner->getNumberOfRailroads() - 1));  // Doubles for each railroad owned
}

void RailroadSquare::buyProperty(Player* player, sf::RenderWindow& window) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->setBalance(player->getBalance() - cost);
        setOwner(player);
        // Additional logic for buying railroad
    }
}

void RailroadSquare::action(Player* player, Board* board, sf::RenderWindow& window) {
    if (owner == nullptr) {
        // Offer to buy railroad
        buyProperty(player, window);
    } else if (owner != player) {
        // Pay rent
        int rent = calculateRent();
        player->payRent(rent, owner, window);
    }
}

void RailroadSquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(sf::Color::White);
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

RailroadSquare::~RailroadSquare() {}