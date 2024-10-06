//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Player.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "RailroadSquare.hpp"
#include "UtilitySquare.hpp"
#include <iostream>

Player::Player(const std::string& playerName, int initialBalance, sf::Color playerColor, bool isAIPlayer)
    : name(playerName), balance(initialBalance), position(0), inJail(false), jailTurns(0), color(playerColor), isAI(isAIPlayer) {
    token.setRadius(10);
    token.setFillColor(color);
}


std::string Player::getName() const { return name; }
int Player::getBalance() const { return balance; }
int Player::getPosition() const { return position; }
bool Player::isInJail() const { return inJail; }

bool Player::tryToEscapeJail() {
    int roll = rollDice();
    if (roll % 2 == 0) {  // שחקן יוצא אם הוא זרק זוגי
        getOutOfJail();
        std::cout << name << " rolled an even number and got out of jail!" << std::endl;
        return true;
    } else {
        std::cout << name << " did not manage to escape jail." << std::endl;
        return false;
    }
}
bool Player::isAIPlayer() const {
    return isAI;
}
void Player::takeAITurn(Board& board) {
    if (isInJail()) {
        tryToEscapeJail();
        return;
    }

    int roll = rollDice();
    move(roll, board);

    Square* landedSquare = board.getSquareAtPosition(position);
    if (PropertySquare* property = dynamic_cast<PropertySquare*>(landedSquare)) {
        if (property->getOwner() == nullptr && balance >= property->getCost()) {
            buyProperty(property);
        }
    }

    std::cout << name << "'s AI turn is complete." << std::endl;
}



sf::Color Player::getColor() const { return color; }
void Player::setBalance(int newBalance) { balance = newBalance; }
void Player::setPosition(int newPosition) { position = newPosition; }

void Player::forfeit() {
    std::cout << name << " has forfeited the game. Returning all properties to the bank." << std::endl;
    properties.clear();  // ה-Smart Pointers דואגים לשחרר את הזיכרון אוטומטית
}

void Player::addProperty(std::unique_ptr<Square> property) {
    properties.push_back(std::move(property));  // הוספת נכס לשחקן
}

std::vector<PropertySquare*> Player::getPropertySquares() const {
    std::vector<PropertySquare*> propertySquares;

    for (const auto& square : properties) {
        if (PropertySquare* propertySquare = dynamic_cast<PropertySquare*>(square.get())) {
            propertySquares.push_back(propertySquare);
        }
    }

    return propertySquares;
}

int Player::getNumberOfRailroads() const {
    int count = 0;
    for (const auto& property : properties) {
        if (dynamic_cast<RailroadSquare*>(property.get()) != nullptr) {
            count++;
        }
    }
    return count;
}

void Player::removeProperty(Square* property) {
    auto it = std::remove_if(properties.begin(), properties.end(),
        [&](const std::unique_ptr<Square>& p) { return p.get() == property; });
    if (it != properties.end()) {
        properties.erase(it, properties.end());  // מסיר את הנכס מהווקטור של הנכסים
        std::cout << name << " no longer owns " << property->getName() << "." << std::endl;
    } else {
        std::cout << "Property not found in " << name << "'s possession." << std::endl;
    }
}

int Player::getNumberOfUtilities() const {
    int count = 0;
    for (const auto& property : properties) {
        if (dynamic_cast<UtilitySquare*>(property.get()) != nullptr) {
            count++;
        }
    }
    return count;
}

void Player::move(int roll, Board& board) {
    int oldPosition = position;
    position = (position + roll) % 40;

    std::cout << name << " moves from " << oldPosition << " to " << position << "." << std::endl;

    Square* landedSquare = board.getSquareAtPosition(position);
    if (landedSquare) {
        std::cout << name << " landed on " << landedSquare->getName() << "." << std::endl;
        landedSquare->action(this, &board);
    } else {
        std::cerr << "Error: Landed on a null square." << std::endl;
    }
}

void Player::incrementJailTurn() {
    jailTurns++;
    if (jailTurns >= 3) {
        getOutOfJail();  // אם עברו 3 תורות, השחקן משתחרר אוטומטית
        std::cout << name << " has been in jail for 3 turns and is now released." << std::endl;
    }
}

int Player::getJailTurns() const {
    return jailTurns;
}

void Player::buyProperty(Square* property) {
    PropertySquare* propertySquare = dynamic_cast<PropertySquare*>(property);

    if (!propertySquare) {
        std::cout << "This square cannot be bought." << std::endl;
        return;
    }

    if (propertySquare->getOwner() != nullptr) {
        std::cout << propertySquare->getName() << " is already owned by " << propertySquare->getOwner()->getName() << "." << std::endl;
        return;
    }

    int cost = propertySquare->getCost();
    if (balance < cost) {
        std::cout << "Not enough money to buy " << propertySquare->getName() << ". Needed: $" << cost << ", Available: $" << balance << "." << std::endl;
        return;
    }

    balance -= cost;
    propertySquare->setOwner(this);
    properties.push_back(std::unique_ptr<Square>(propertySquare));

    std::cout << name << " bought " << propertySquare->getName() << " for $" << cost << "." << std::endl;
}

void Player::offerLoan(Player* otherPlayer, int amount, int interestRate) {
    if (balance >= amount) {
        balance -= amount;
        otherPlayer->addMoney(amount);
        std::cout << name << " loaned $" << amount << " to " << otherPlayer->getName() 
                  << " with an interest rate of " << interestRate << "%" << std::endl;
    } else {
        std::cout << name << " doesn't have enough money to offer a loan." << std::endl;
    }
}

void Player::repayLoan(int amount, Player* lender) {
    if (balance >= amount) {
        balance -= amount;
        lender->addMoney(amount);
        std::cout << name << " repaid $" << amount << " to " << lender->getName() << std::endl;
    } else {
        std::cout << name << " doesn't have enough money to repay the loan." << std::endl;
    }
}

void Player::payRent(int amount, Player* owner) {
    if (balance > amount) {
        balance -= amount;
        if (owner) {
            owner->addMoney(amount);
        }
    } else {
        std::cout << name << " cannot afford to pay $" << amount << " in rent." << std::endl;
    }
}

void Player::addMoney(int amount) {
    balance += amount;
    std::cout << name << " received $" << amount << std::endl;
}

void Player::sendToJail() {
    inJail = true;
    jailTurns = 0;  // מאפסים את מספר התורות בכלא
    position = 10;  // Jail position
    std::cout << name << " was sent to jail." << std::endl;
}

void Player::getOutOfJail() {
    inJail = false;
    jailTurns = 0;  // מאפסים את מספר התורות בכלא לאחר יציאה
    std::cout << name << " is out of jail." << std::endl;
}

int Player::rollDice() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

bool Player::isBankrupt() const {
    return balance < 0;
}

int Player::getTotalMortgageValue() const {
    int totalValue = 0;
    for (const auto& square : properties) {
        PropertySquare* propertySquare = dynamic_cast<PropertySquare*>(square.get());
        if (propertySquare != nullptr && propertySquare->isMortgaged()) {
            totalValue += propertySquare->getMortgageValue();
        }
    }
    return totalValue;
}

void Player::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void Player::render(sf::RenderWindow& window, const sf::Font& font) const {
    window.draw(token);

    sf::Text playerInfo;
    playerInfo.setFont(font);
    playerInfo.setCharacterSize(14);
    playerInfo.setFillColor(sf::Color::Black);
    playerInfo.setString(name + ": $" + std::to_string(balance));

    sf::FloatRect textBounds = playerInfo.getLocalBounds();
    playerInfo.setOrigin(textBounds.width / 2, textBounds.height / 2);
    playerInfo.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 100);

    window.draw(playerInfo);
}

Player::~Player() {
    // ה-Smart Pointers דואגים לשחרור הזיכרון אוטומטית
}
