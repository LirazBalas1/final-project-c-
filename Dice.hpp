//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef DICE_H
#define DICE_H

#include <SFML/Graphics.hpp>

class Dice {
private:
    int die1;  // First die result
    int die2;  // Second die result
    int doublesCount;  // Number of consecutive doubles rolled
    int total ;

    // Graphical components for rendering dice
    sf::RectangleShape die1Shape;  // Name should be consistent
    sf::RectangleShape die2Shape;  // Name should be consistent
    sf::Text die1Text;  // Name should be consistent
    sf::Text die2Text;  // Name should be consistent
    sf::Font font;  // Make sure this matches with the implementation

public:
    Dice();

    // Roll both dice
    int roll();

    // Getters
    int getDie1() const;
    int getDie2() const;
    int getTotal() const;
    bool isDouble() const;
    int getDoublesCount() const;
    void setTotal(int newTotal);

    // Reset doubles count
    void resetDoublesCount();

    // Render dice results
    void render(sf::RenderWindow& window);
};

#endif // DICE_H
