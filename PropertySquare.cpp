//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "PropertySquare.hpp"
#include "Player.hpp"
#include <iostream>

PropertySquare::PropertySquare(const std::string& propertyName, int propertyCost, int propertyRent, const sf::Color& propertyColor)
    : Square(propertyName), cost(propertyCost), baseRent(propertyRent), owner(nullptr), houses(0), hotels(0), mortgaged(false), mortgageValue(propertyCost / 2), color(propertyColor) {}

int PropertySquare::getCost() const {
    return cost;
}

int PropertySquare::getBaseRent() const {
    return baseRent;
}
int PropertySquare::getMortgageValue() const {
    return mortgageValue; // מחזיר את ערך המשכנתא
}

bool PropertySquare::isMortgaged() const {
    return mortgaged; // בדיקה אם הנכס נמצא במשכנתא
}

void PropertySquare::setMortgaged(bool mortgaged) {
    this->mortgaged = mortgaged; // הגדרת משכנתא
}

void PropertySquare::setOwner(Player* newOwner) {
    owner = newOwner; // הגדרת בעלים חדש לנכס
}

Player* PropertySquare::getOwner() const {
    return owner; // מחזיר את הבעלים הנוכחי
}
 sf::Color PropertySquare::getColor() const { return sf::Color(128, 128, 128); }

void PropertySquare::buyProperty(Player* player) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->addMoney(-cost); // הורדת העלות מהשחקן
        setOwner(player);
        player->addProperty(std::make_unique<PropertySquare>(*this));  // יצירת עותק של הנכס והוספתו לרשימת השחקן
        player->displayMessage(player->getName() + " bought " + getName() + " for $" + std::to_string(cost));
    } else if (owner != nullptr) {
        player->displayMessage(getName() + " is already owned by " + owner->getName());
    } else {
        player->displayMessage(player->getName() + " does not have enough money to buy " + getName());
    }
}

int PropertySquare::calculateRent() const {
    if (hotels > 0) {
        return baseRent * 5;  // שכר דירה אם יש מלון
    }
    return baseRent * (1 << houses);  // שכר דירה מוכפל בהתאם למספר הבתים
}

void PropertySquare::buildHouse() {
    if (canBuildHouse()) {
        houses++; // הוספת בית לנכס
        std::cout << "Built a house on " << getName() << ". Now there are " << houses << " houses." << std::endl;
    }
}

void PropertySquare::buildHotel() {
    if (canBuildHotel()) {
        hotels++; // הוספת מלון
        houses = 0;  // מלון מחליף את כל הבתים
        std::cout << "Built a hotel on " << getName() << "." << std::endl;
    }
}

bool PropertySquare::canBuildHouse() const {
    return houses < 4 && hotels == 0;  // ניתן לבנות עד 4 בתים אם אין מלון
}

bool PropertySquare::canBuildHotel() const {
    return houses == 4;  // ניתן לבנות מלון רק אחרי 4 בתים
}

void PropertySquare::action(Player* player, Board* board) {
    if (owner == nullptr) {
        buyProperty(player); // הצעת רכישת הנכס
    } else if (owner != player) {
        int rent = calculateRent();
        player->payRent(rent, owner); // תשלום שכר דירה
        player->displayMessage(player->getName() + " landed on " + getName() + " and owes $" + std::to_string(rent) + " in rent.");
    }
}
void PropertySquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
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

PropertySquare::~PropertySquare() {
    // ניקוי זיכרון אם נדרש
}
