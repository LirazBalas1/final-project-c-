//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef DICE_HPP
#define DICE_HPP

#include <SFML/Graphics.hpp>

class Dice {
private:
    int die1;  // First die result
    int die2;  // Second die result
    int doublesCount;  // Number of consecutive doubles rolled

    // Graphical components for rendering dice
    sf::RectangleShape die1Shape;
    sf::RectangleShape die2Shape;
    sf::Text die1Text;
    sf::Text die2Text;
    sf::Font font;

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

    // Reset doubles count
    void resetDoublesCount();

    // Render dice results
    void render(sf::RenderWindow& window);
};

#endif // DICE_HPP
