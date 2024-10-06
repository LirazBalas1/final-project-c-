//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef COMMUNITYCHESTSQUARE_H
#define COMMUNITYCHESTSQUARE_H

#include "Square.hpp"

class CommunityChestSquare : public Square {
    private:
    sf::Color color;
public:
    CommunityChestSquare();

    sf::Color getColor() const override ;
    void action(Player* player, Board* board) override; // Updated to remove window parameter
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~CommunityChestSquare();
};

#endif // COMMUNITYCHESTSQUARE_H
