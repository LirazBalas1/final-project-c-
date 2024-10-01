//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "PropertySquare.hpp"
#include "Player.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

PropertySquare::PropertySquare(const std::string& propertyName, int propertyCost, int propertyRent)
    : Square(propertyName), cost(propertyCost), baseRent(propertyRent), owner(nullptr), houses(0), hotels(0) {}

int PropertySquare::getCost() const {
    return cost;
}

int PropertySquare::getBaseRent() const {
    return baseRent;
}
void PropertySquare::buyProperty(Player* player, sf::RenderWindow& window) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->setBalance(player->getBalance() - cost);
        setOwner(player);
        player->buyProperty(this, window);  // Changed from buySquare to buyProperty


        std::cout << player->getName() << " bought " << getName() << " for " << cost << std::endl;

        // Display purchase on game window
        sf::Font font;
        if (!font.loadFromFile("Roboto-Black.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }
        sf::Text message;
        message.setFont(font);
        message.setString(player->getName() + " bought " + getName() + " for $" + std::to_string(cost));
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::Black);
        message.setPosition(10, 10);

        window.clear(sf::Color::White);
        window.draw(message);
        window.display();

        sf::sleep(sf::seconds(2));
    } else if (owner != nullptr) {
        std::cout << getName() << " is already owned by " << owner->getName() << std::endl;

        sf::Font font;
        if (!font.loadFromFile("Roboto-Black.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }
        sf::Text message;
        message.setFont(font);
        message.setString(getName() + " is already owned by " + owner->getName());
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::Red);
        message.setPosition(10, 10);

        window.clear(sf::Color::White);
        window.draw(message);
        window.display();

        sf::sleep(sf::seconds(2));
    } else {
        std::cout << player->getName() << " doesn't have enough money to buy " << getName() << std::endl;

        sf::Font font;
        if (!font.loadFromFile("Roboto-Black.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }
        sf::Text message;
        message.setFont(font);
        message.setString(player->getName() + " doesn't have enough money to buy " + getName());
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::Red);
        message.setPosition(10, 10);

        window.clear(sf::Color::White);
        window.draw(message);
        window.display();

        sf::sleep(sf::seconds(2));
    }
}

int PropertySquare::calculateRent() const {
    if (hotels > 0) {
        return baseRent * 5;  // Rent with a hotel
    }
    return baseRent * (1 << houses);  // Rent increases by a factor of 2 per house
}

void PropertySquare::buildHouse() {
    if (canBuildHouse()) {
        houses++;
        std::cout << "A house was built on " << getName() << std::endl;
    }
}

void PropertySquare::buildHotel() {
    if (canBuildHotel()) {
        hotels++;
        houses = 0;  // A hotel replaces the houses
        std::cout << "A hotel was built on " << getName() << std::endl;
    }
}

bool PropertySquare::canBuildHouse() const {
    return houses < 4 && hotels == 0;  // Up to 4 houses can be built
}

bool PropertySquare::canBuildHotel() const {
    return houses == 4;  // A hotel can only be built after 4 houses
}

void PropertySquare::action(Player* player, Board* board, sf::RenderWindow& window) {
    if (owner == nullptr) {
        std::cout << player->getName() << " can buy " << getName() << " for " << cost << std::endl;
        std::cout << "Would you like to buy it? (y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y') {
            buyProperty(player, window);
        }
    } else if (owner != player) {
        int rent = calculateRent();
        std::cout << player->getName() << " landed on " << getName() << " and owes " << rent << " in rent." << std::endl;

        sf::Font font;
        if (!font.loadFromFile("Roboto-Black.ttf")) {
            std::cerr << "Error loading font for rent display!" << std::endl;
            return;
        }

        sf::Text message;
        message.setFont(font);
        message.setString(player->getName() + " owes " + std::to_string(rent) + " in rent to " + owner->getName());
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::Black);
        message.setPosition(10, 10);

        window.clear(sf::Color::White);
        window.draw(message);
        window.display();

        sf::sleep(sf::seconds(2));

        player->payRent(rent, owner, window);
    } else {
        std::cout << player->getName() << " owns " << getName() << std::endl;

        sf::Font font;
        if (!font.loadFromFile("Roboto-Black.ttf")) {
            std::cerr << "Error loading font for ownership display!" << std::endl;
            return;
        }

        sf::Text message;
        message.setFont(font);
        message.setString(player->getName() + " owns " + getName());
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::Black);
        message.setPosition(10, 10);

        window.clear(sf::Color::White);
        window.draw(message);
        window.display();

        sf::sleep(sf::seconds(2));
    }
}

PropertySquare::~PropertySquare() {
}
