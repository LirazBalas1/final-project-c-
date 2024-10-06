//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "CommunityChestSquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

CommunityChestSquare::CommunityChestSquare() : Square("Community Chest") {}

void CommunityChestSquare::action(Player* player, Board* board) {
    std::cout << player->getName() << " landed on Community Chest!" << std::endl;
    Card* card = board->drawCommunityChestCard(); // Get a community chest card from the board

    if (card) {
        std::cout << "Drew a Community Chest card: " << card->getDescription() << std::endl;
        card->applyToPlayer(player, board); // Apply the card's effect to the player
        player->displayMessage("Drew a Community Chest card: " + card->getDescription());
    } else {
        player->displayMessage("No Community Chest cards left!");
    }
}
sf::Color CommunityChestSquare::getColor() const  {
        return sf::Color::Magenta;  // ורוד
    }
void CommunityChestSquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    sf::Color lightBlue(173, 216, 230);
    square.setFillColor(lightBlue);
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.0f);
    window.draw(square);

    sf::Text nameText("Community", font, 10);
    nameText.setPosition(position.x + 5, position.y + 5);
    nameText.setFillColor(sf::Color::Black);
    window.draw(nameText);

    sf::Text chestText("Chest", font, 10);
    chestText.setPosition(position.x + 5, position.y + 20);
    chestText.setFillColor(sf::Color::Black);
    window.draw(chestText);
}

CommunityChestSquare::~CommunityChestSquare() {}
