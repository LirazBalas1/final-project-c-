//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "CommunityChestSquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

CommunityChestSquare::CommunityChestSquare() : Square("Community Chest") {}

void CommunityChestSquare::action(Player* player, Board* board, sf::RenderWindow& window) {
    std::cout << player->getName() << " landed on Community Chest!" << std::endl;
    Card* card = board->drawCommunityChestCard();
    if (card) {
        card->applyToPlayer(player, board, window);
    } else {
        std::cout << "No Community Chest cards left!" << std::endl;
    }
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