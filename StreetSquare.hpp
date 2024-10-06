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
    int cost;               // עלות הנכס
    int baseRent;           // שכר דירה בסיסי ללא בתים או בתי מלון
    Player* owner;          // בעל הנכס
    int houses;             // מספר הבתים שנבנו בנכס
    int hotels;             // מספר בתי המלון בנכס
    sf::Color color;        // צבע הנכס

public:
    StreetSquare(const std::string& name, int cost, int baseRent, const sf::Color& color);
     sf::Color getColor() const override ; // מימוש של הפונקציה

    int getCost() const;
    int calculateRent() const;
    void buildHouse();
    void buildHotel();
    bool canBuildHouse() const;
    bool canBuildHotel() const;
    void buyProperty(Player* player);
    void setOwner(Player* newOwner) override;
    Player* getOwner() const override;

    void action(Player* player, Board* board) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~StreetSquare() override;  // שימוש במילה override ל-Destructor
};

#endif // STREET_SQUARE_H
