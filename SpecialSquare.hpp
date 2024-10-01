//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef SPECIALSQUARE_H
#define SPECIALSQUARE_H

#include "Square.hpp"

class SpecialSquare : public Square {
public:
    SpecialSquare(const std::string& name);

    void action(Player* player, Board* board, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~SpecialSquare();
};

#endif // SPECIALSQUARE_H