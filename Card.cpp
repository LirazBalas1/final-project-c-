//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Card.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

Card::Card(const std::string& desc, int amt) : description(desc), amount(amt) {}

std::string Card::getDescription() const {
    return description;
}

int Card::getAmount() const {
    return amount;
}

void Card::applyToPlayer(Player* player, Board* board) {
    std::cout << player->getName() << " drew a card: " << description << std::endl;

    if (amount != 0) {
        std::cout << "Applying money effect: " << amount << std::endl;
        player->addMoney(amount);
    } else if (description == "Advance to Go (Collect $200)") {
        std::cout << "Applying Go effect" << std::endl;
        player->setPosition(0);
        player->addMoney(200);
    } else if (description == "Go to Jail") {
        std::cout << "Sending player to jail" << std::endl;
        player->sendToJail();
    } else if (description == "Bank error in your favor—Collect $200") {
        std::cout << "Bank error: Player gets $200" << std::endl;
        player->addMoney(200);
    }
}


void Card::render(sf::RenderWindow& window, const sf::Font& font) const {
    // פונקציה לציור הקלף על המסך, במידת הצורך
    sf::Text cardText(description, font, 14);
    cardText.setPosition(10, 10);  // דוגמה למיקום הקלף
    cardText.setFillColor(sf::Color::Black);
    window.draw(cardText);
}
