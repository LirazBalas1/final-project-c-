//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "SpecialSquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

SpecialSquare::SpecialSquare(const std::string& name) : Square(name) {}

void SpecialSquare::action(Player* player, Board* board) {
    if (name == "GO") {
        player->addMoney(200); // השחקן מקבל $200
        player->displayMessage(player->getName() + " landed on " + name + " and collected $200.");
    } else if (name == "Income Tax") {
        player->payRent(200, nullptr); // תשלום של $200 לבנק
        player->displayMessage(player->getName() + " landed on " + name + " and must pay $200 in taxes.");
    } else if (name == "Luxury Tax") {
        player->payRent(75, nullptr); // תשלום של $75 לבנק
        player->displayMessage(player->getName() + " landed on " + name + " and must pay $75 in luxury tax.");
    } else if (name == "Go to Jail") {
        player->sendToJail(); // שולח את השחקן לכלא
        player->displayMessage(player->getName() + " is going to Jail!");
    } else if (name == "Free Parking") {
        player->displayMessage(player->getName() + " is relaxing on Free Parking!");
    } else if (name == "Jail") {
        player->displayMessage(player->getName() + " is just visiting Jail.");
    }
}
sf::Color SpecialSquare::getColor() const {
   if (name == "Go to Jail") {
            return sf::Color::Red;
        } else if (name == "Free Parking") {
            return sf::Color::Green;
        }
        return sf::Color::Yellow;  // 'Go' ואחרים
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

    if (name == "GO") {
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
