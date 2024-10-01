//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef RAILROADSQUARE_H
#define RAILROADSQUARE_H

#include "Square.hpp"
#include "Player.hpp"

class RailroadSquare : public Square {
private:
    int cost;
    int baseRent;
    Player* owner;

public:
    RailroadSquare(const std::string& name, int cost);

    void setOwner(Player* newOwner) override { owner = newOwner; }
    Player* getOwner() const override { return owner; }
    
    int getCost() const;
    int calculateRent() const;
    void buyProperty(Player* player, sf::RenderWindow& window);
    

    void action(Player* player, Board* board, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~RailroadSquare();
};

#endif // RAILROADSQUARE_H