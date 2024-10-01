//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "StreetSquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

StreetSquare::StreetSquare(const std::string& name, int cost, int baseRent, const sf::Color& color)
    : Square(name), cost(cost), baseRent(baseRent), owner(nullptr), houses(0), hotels(0), color(color) {}

int StreetSquare::getCost() const {
    return cost;
}

int StreetSquare::calculateRent() const {
    if (owner == nullptr) return 0;
    if (hotels > 0) return baseRent * 5;
    return baseRent * (1 << houses);  // Doubles for each house
}

void StreetSquare::buildHouse() {
    if (canBuildHouse()) houses++;
}

void StreetSquare::buildHotel() {
    if (canBuildHotel()) {
        hotels++;
        houses = 0;
    }
}

bool StreetSquare::canBuildHouse() const {
    return houses < 4 && hotels == 0;
}

bool StreetSquare::canBuildHotel() const {
    return houses == 4 && hotels == 0;
}

void StreetSquare::buyProperty(Player* player, sf::RenderWindow& window) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->setBalance(player->getBalance() - cost);
        setOwner(player);
        // Additional logic for buying property
    }
}

Player* StreetSquare::getOwner() const {
    return owner;
}

void StreetSquare::setOwner(Player* newOwner) {
    owner = newOwner;
}

sf::Color StreetSquare::getColor() const {
    return color;
}

void StreetSquare::action(Player* player, Board* board, sf::RenderWindow& window) {
    if (owner == nullptr) {
        // Offer to buy property
        buyProperty(player, window);
    } else if (owner != player) {
        // Pay rent
        int rent = calculateRent();
        player->payRent(rent, owner, window);
    }
}

void StreetSquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(color);
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

StreetSquare::~StreetSquare() {}