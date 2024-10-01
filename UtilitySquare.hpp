//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef UTILITYSQUARE_H
#define UTILITYSQUARE_H

#include "Square.hpp"
#include "Player.hpp"

class UtilitySquare : public Square {
private:
    int cost;
    Player* owner;

public:
    UtilitySquare(const std::string& name, int cost);

    int getCost() const;
    int calculateRent(int diceRoll) const;
    void buyProperty(Player* player, sf::RenderWindow& window);
    void setOwner(Player* newOwner) override { owner = newOwner; }
    Player* getOwner() const override { return owner; }

    void action(Player* player, Board* board, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~UtilitySquare();
};

#endif // UTILITYSQUARE_H