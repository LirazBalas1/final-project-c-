//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef COMMUNITYCHESTSQUARE_H
#define COMMUNITYCHESTSQUARE_H

#include "Square.hpp"

class CommunityChestSquare : public Square {
public:
    CommunityChestSquare();

    void action(Player* player, Board* board, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~CommunityChestSquare();
};

#endif // COMMUNITYCHESTSQUARE_H