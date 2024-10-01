//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "ChanceSquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

ChanceSquare::ChanceSquare() : Square("Chance") {}

void ChanceSquare::action(Player* player, Board* board, sf::RenderWindow& window) {
    std::cout << player->getName() << " landed on Chance!" << std::endl;
    Card* card = board->drawChanceCard();
    if (card) {
        card->applyToPlayer(player, board, window);
    } else {
        std::cout << "No Chance cards left!" << std::endl;
    }
}

void ChanceSquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(sf::Color::Yellow);
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.0f);
    window.draw(square);

    sf::Text nameText(name, font, 12);
    nameText.setPosition(position.x + 5, position.y + size / 2 - 10);
    nameText.setFillColor(sf::Color::Black);
    window.draw(nameText);

    sf::Text questionMark("?", font, 24);
    questionMark.setPosition(position.x + size / 2 - 7, position.y + size / 2 - 20);
    questionMark.setFillColor(sf::Color::Black);
    window.draw(questionMark);
}

ChanceSquare::~ChanceSquare() {}