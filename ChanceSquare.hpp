//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef CHANCESQUARE_H
#define CHANCESQUARE_H

#include "Square.hpp"

class ChanceSquare : public Square {
    private: 
    sf::Color color;
public:
    ChanceSquare();

    sf::Color getColor() const override ;
    void action(Player* player, Board* board) override; // Updated to remove window parameter
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~ChanceSquare();
};

#endif // CHANCESQUARE_H
