//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "RailroadSquare.hpp"
#include "Player.hpp"
#include <iostream>

RailroadSquare::RailroadSquare(const std::string& name, int cost)
    : Square(name), cost(cost), baseRent(25), owner(nullptr) {}

int RailroadSquare::getCost() const {
    return cost;
}

int RailroadSquare::calculateRent() const {
    if (owner == nullptr) return 0;
    return baseRent * (1 << (owner->getNumberOfRailroads() - 1)); // מכפילים את שכר הדירה עבור כל רכבת בבעלות
}

void RailroadSquare::displayMessage(Player* player, const std::string& message) {
    std::cout << message << std::endl; // שליחת הודעות למסוף
}

void RailroadSquare::buyProperty(Player* player) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->addMoney(-cost); // Deduct cost from player's balance
        setOwner(player);
        player->addProperty(std::unique_ptr<Square>(new RailroadSquare(*this)));  // הוספת הרכוש לרשימת הרכוש של השחקן כ-unique_ptr
        displayMessage(player, player->getName() + " bought " + getName() + " for $" + std::to_string(cost));
    } else if (owner != nullptr) {
        displayMessage(player, getName() + " is already owned by " + owner->getName());
    } else {
        displayMessage(player, player->getName() + " does not have enough money to buy " + getName());
    }
}


void RailroadSquare::action(Player* player, Board* board) {
    if (owner == nullptr) {
        // הצעה לקנות את הרכבת
        buyProperty(player);
    } else if (owner != player) {
        // תשלום שכירות
        int rent = calculateRent();
        player->payRent(rent, owner);
        displayMessage(player, player->getName() + " landed on " + getName() + " and owes $" + std::to_string(rent) + " in rent.");
    }
}

void RailroadSquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(sf::Color(200, 200, 200)); // צבע אפור בהיר לרכבת
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

RailroadSquare::~RailroadSquare() {
    // שחרור זיכרון אם נדרש
}
