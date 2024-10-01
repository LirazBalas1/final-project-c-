//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Card.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

Card::Card(const std::string& desc, int amt) : description(desc), amount(amt) {}

std::string Card::getDescription() const { return description; }
int Card::getAmount() const { return amount; }

void Card::applyToPlayer(Player* player, Board* board, sf::RenderWindow& window) {
    std::cout << player->getName() << " drew a card: " << description << std::endl;

    if (amount != 0) {
        player->addMoney(amount, window);
    } else if (description == "Advance to Go") {
        player->setPosition(0);
        player->addMoney(200, window);
    } else if (description == "Go to Jail") {
        player->sendToJail(window);
    }
    // Add more specific card actions here
}

void Card::render(sf::RenderWindow& window, const sf::Font& font) const {
    sf::Text cardText;
    cardText.setFont(font);
    cardText.setCharacterSize(12);
    cardText.setFillColor(sf::Color::Black);
    cardText.setString(description);
    cardText.setPosition(400, 300);  // Adjust position as needed
    window.draw(cardText);
}