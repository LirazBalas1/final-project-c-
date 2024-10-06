//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef SPECIALSQUARE_H
#define SPECIALSQUARE_H

#include "Square.hpp"

class SpecialSquare : public Square {
private:
 sf::Color color;
public:
    SpecialSquare(const std::string& name);

    sf::Color getColor() const override;

    void action(Player* player, Board* board) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~SpecialSquare() override;  // שימוש במילה override עבור ה-Destructor
};

#endif // SPECIALSQUARE_H
