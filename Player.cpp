//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Player.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "PropertySquare.hpp"
#include "RailroadSquare.hpp"
#include "UtilitySquare.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Player::Player(const std::string& playerName, int initialBalance, sf::Color playerColor)
    : name(playerName), balance(initialBalance), position(0), inJail(false), jailTurns(0), color(playerColor) {
    token.setRadius(10);
    token.setFillColor(color);
}

std::string Player::getName() const { return name; }
int Player::getBalance() const { return balance; }
int Player::getPosition() const { return position; }
bool Player::isInJail() const { return inJail; }
sf::Color Player::getColor() const { return color; }

void Player::setBalance(int newBalance) { balance = newBalance; }
void Player::setPosition(int newPosition) { position = newPosition; }

std::vector<PropertySquare*> Player::getPropertySquares() const {
    std::vector<PropertySquare*> propertySquares;
    for (auto* property : properties) {
        if (auto* propertySquare = dynamic_cast<PropertySquare*>(property)) {
            propertySquares.push_back(propertySquare);
        }
    }
    return propertySquares;
}

void Player::move(int steps, Board& board, sf::RenderWindow& window) {
    int newPosition = (position + steps) % 40;
    if (newPosition < position) {
        addMoney(200, window);
    }
    position = newPosition;
    
    Square* landedSquare = board.getSquareAtPosition(position);
    landedSquare->action(this, &board, window);
}

void Player::displayMessage(sf::RenderWindow& window, const std::string& message) {
    sf::Font font;
    if (!font.loadFromFile("Roboto-Black.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    sf::Text messageText(message, font, 20);
    messageText.setPosition(200, 250);

    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2) {
        window.clear(sf::Color::White);
        window.draw(messageText);
        window.display();
    }
}

void Player::buyProperty(Square* property, sf::RenderWindow& window) {
    PropertySquare* propertySquare = dynamic_cast<PropertySquare*>(property);
    if (propertySquare) {
        int cost = propertySquare->getCost();
        if (balance >= cost) {
            balance -= cost;
            properties.push_back(propertySquare);
            propertySquare->setOwner(this);
            displayMessage(window, getName() + " bought " + propertySquare->getName() + " for $" + std::to_string(cost));
        } else {
            displayMessage(window, "Not enough money to buy " + propertySquare->getName());
        }
    } else {
        displayMessage(window, "This square cannot be bought.");
    }
}

void Player::payRent(int amount, Player* owner, sf::RenderWindow& window) {
    if (balance >= amount) {
        balance -= amount;
        if (owner) {
            owner->addMoney(amount, window);
        }
        displayMessage(window, getName() + " paid $" + std::to_string(amount) + " in rent.");
    } else {
        // Handle bankruptcy
        int availableFunds = balance + getTotalMortgageValue();

        if (availableFunds >= amount) {
            // Player can avoid bankruptcy by mortgaging properties
            while (balance < amount) {
                Square* propertyToMortgage = selectPropertyToMortgage(window);
                if (propertyToMortgage) {
                    mortgage(propertyToMortgage, window);
                } else {
                    break; // Player chose not to mortgage more properties
                }
            }
            
            // Try to pay rent again
            if (balance >= amount) {
                balance -= amount;
                if (owner) {
                    owner->addMoney(amount, window);
                }
                displayMessage(window, getName() + " paid $" + std::to_string(amount) + " in rent after mortgaging properties.");
            } else {
                declareBankruptcy(owner, window);
            }
        } else {
            // Player doesn't have enough even after mortgaging everything
            declareBankruptcy(owner, window);
        }
    }
}

Square* Player::selectPropertyToMortgage(sf::RenderWindow& window) {
    std::vector<Square*> mortgageableProperties;
    for (auto property : properties) {
        if (!property->isMortgaged()) {
            mortgageableProperties.push_back(property);
        }
    }

    if (mortgageableProperties.empty()) {
        return nullptr;
    }

    // TODO: Implement SFML-based property selection GUI
    // For now, we'll just return the first mortgageable property
    return mortgageableProperties[0];
}

void Player::mortgage(Square* property, sf::RenderWindow& window) {
    if (property && !property->isMortgaged()) {
        balance += property->getMortgageValue();
        property->setMortgaged(true);
        displayMessage(window, getName() + " mortgaged " + property->getName() + " for $" + std::to_string(property->getMortgageValue()));
    }
}

void Player::declareBankruptcy(Player* creditor, sf::RenderWindow& window) {
    displayMessage(window, getName() + " has gone bankrupt!");

    if (creditor) {
        // Transfer all assets to the creditor
        for (auto property : properties) {
            property->setOwner(creditor);
            creditor->addProperty(property);
        }
        creditor->addMoney(balance, window);
        displayMessage(window, creditor->getName() + " received all assets from " + getName());
    } else {
        // Bankrupt to the bank, return all properties to the bank
        for (auto property : properties) {
            property->setOwner(nullptr);
            property->setMortgaged(false);
        }
        displayMessage(window, "All properties of " + getName() + " returned to the bank");
    }

    // Clear player's properties and set balance to 0
    properties.clear();
    balance = 0;
    
    // Update player status
    inJail = false;
    jailTurns = 0;

    displayMessage(window, getName() + " has been removed from the game");
}

void Player::addMoney(int amount, sf::RenderWindow& window) {
    balance += amount;
    displayMessage(window, getName() + " received $" + std::to_string(amount));
}

void Player::sendToJail(sf::RenderWindow& window) {
    inJail = true;
    position = 10;  // Jail position
    jailTurns = 0;
    displayMessage(window, getName() + " was sent to jail!");
}

void Player::getOutOfJail() {
    inJail = false;
    jailTurns = 0;
}

int Player::rollDice() {
    return (rand() % 6) + 1 + (rand() % 6) + 1;
}

bool Player::isBankrupt() const {
    return balance <= 0 && properties.empty();
}

int Player::getTotalMortgageValue() const {
    int totalValue = 0;
    for (auto property : properties) {
        totalValue += property->getMortgageValue();
    }
    return totalValue;
}

int Player::getNumberOfRailroads() const {
    return std::count_if(properties.begin(), properties.end(), 
                         [](const Square* p) { return dynamic_cast<const RailroadSquare*>(p) != nullptr; });
}

int Player::getNumberOfUtilities() const {
    return std::count_if(properties.begin(), properties.end(), 
                         [](const Square* p) { return dynamic_cast<const UtilitySquare*>(p) != nullptr; });
}

void Player::render(sf::RenderWindow& window, const sf::Font& font) const {
    // Render player token on the board
    window.draw(token);

    // Render player info
    sf::Text playerInfo;
    playerInfo.setFont(font);
    playerInfo.setCharacterSize(12);
    playerInfo.setFillColor(color);
    playerInfo.setString(name + ": $" + std::to_string(balance));
    playerInfo.setPosition(10, 10 + 20 * position);  // Adjust position as needed
    window.draw(playerInfo);
}

Player::~Player() {}