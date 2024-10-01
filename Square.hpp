//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <SFML/Graphics.hpp>

class Player;
class Board;

class Square {
protected:
    std::string name;

public:
    Square(const std::string& squareName);

    virtual void action(Player* player, Board* board, sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) = 0;
    virtual int getMortgageValue() const { return 0; }
    virtual bool isMortgaged() const { return false; }
    virtual void setMortgaged(bool mortgaged) {}
    virtual void setOwner(Player* newOwner) {} // Default empty implementation
    virtual Player* getOwner() const { return nullptr; } // Default implementation
    std::string getName() const;

    virtual ~Square();
};

#endif // SQUARE_H