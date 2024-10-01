//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef CHANCESQUARE_H
#define CHANCESQUARE_H

#include "Square.hpp"

class ChanceSquare : public Square {
public:
    ChanceSquare();

    void action(Player* player, Board* board, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~ChanceSquare();
};

#endif // CHANCESQUARE_H