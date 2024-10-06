//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "StreetSquare.hpp"
#include "Player.hpp"
#include <iostream>

StreetSquare::StreetSquare(const std::string& name, int cost, int baseRent, const sf::Color& color)
    : Square(name), cost(cost), baseRent(baseRent), owner(nullptr), houses(0), hotels(0), color(color) {}

int StreetSquare::getCost() const {
    return cost;
}

int StreetSquare::calculateRent() const {
    if (hotels > 0) {
        return baseRent * 5;  // שכר דירה עם בית מלון
    }
    return baseRent * (1 << houses);  // שכר דירה עולה פי 2 עבור כל בית שנבנה
}

void StreetSquare::buildHouse() {
    if (canBuildHouse()) {
        houses++;
    }
}

void StreetSquare::buildHotel() {
    if (canBuildHotel()) {
        hotels++;
        houses = 0;  // בית מלון מחליף את כל הבתים
    }
}

bool StreetSquare::canBuildHouse() const {
    return houses < 4 && hotels == 0;  // ניתן לבנות עד 4 בתים, אלא אם יש בית מלון
}

bool StreetSquare::canBuildHotel() const {
    return houses == 4;  // ניתן לבנות בית מלון רק לאחר 4 בתים
}

void StreetSquare::buyProperty(Player* player) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->addMoney(-cost);  // ניכוי עלות מהשחקן
        setOwner(player);
        player->addProperty(std::make_unique<StreetSquare>(*this));  // יצירת עותק של הנכס והוספתו לרשימת השחקן
        player->displayMessage(player->getName() + " bought " + getName() + " for $" + std::to_string(cost));
    } else if (owner != nullptr) {
        player->displayMessage(getName() + " is already owned by " + owner->getName());
    } else {
        player->displayMessage(player->getName() + " does not have enough money to buy " + getName());
    }
}

void StreetSquare::setOwner(Player* newOwner) {
    owner = newOwner;
}

Player* StreetSquare::getOwner() const {
    return owner;
}

sf::Color StreetSquare::getColor() const {
    return color;  // החזרת הצבע של הנכס
}

void StreetSquare::action(Player* player, Board* board) {
    if (owner == nullptr) {
        // הצעת רכישת הנכס
        buyProperty(player);
    } else if (owner != player) {
        // תשלום שכר דירה
        int rent = calculateRent();
        player->payRent(rent, owner);
        player->displayMessage(player->getName() + " landed on " + getName() + " and owes $" + std::to_string(rent) + " in rent.");
    }
}

void StreetSquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(color);
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.0f);
    window.draw(square);

    sf::Text nameText(getName(), font, 10);
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

StreetSquare::~StreetSquare() {
    // Destructor לא דורש שחרור זיכרון נוסף כי אין הקצאות דינמיות
}
