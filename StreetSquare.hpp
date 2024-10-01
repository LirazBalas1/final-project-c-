//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef STREET_SQUARE_H
#define STREET_SQUARE_H

#include "Square.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class StreetSquare : public Square {
private:
    int cost;
    int baseRent;
    Player* owner;
    int houses;
    int hotels;
    sf::Color color;

public:
    StreetSquare(const std::string& name, int cost, int baseRent, const sf::Color& color);

    int getCost() const;
    int calculateRent() const;
    void buildHouse();
    void buildHotel();
    bool canBuildHouse() const;
    bool canBuildHotel() const;
    void buyProperty(Player* player, sf::RenderWindow& window);
    void setOwner(Player* newOwner) override ;
    Player* getOwner() const override;
    sf::Color getColor() const;

    void action(Player* player, Board* board, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~StreetSquare();
};

#endif // STREET_SQUARE_H