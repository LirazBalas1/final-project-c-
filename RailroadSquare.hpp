//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef RAILROADSQUARE_H
#define RAILROADSQUARE_H

#include "Square.hpp"
#include "Player.hpp"

class RailroadSquare : public Square {
private:
    int cost;               // עלות הרכבת
    int baseRent;           // שכר דירה בסיסי עבור רכבת
    Player* owner;          // הבעלים של הרכבת
    sf::Color color;
public:
    RailroadSquare(const std::string& name, int cost);
    sf::Color getColor() const override { return color; }  // מימוש של הפונקציה
    void displayMessage(Player* player, const std::string& message);
    void setOwner(Player* newOwner) override { owner = newOwner; }
    Player* getOwner() const override { return owner; }
    
    int getCost() const;
    int calculateRent() const;
    void buyProperty(Player* player); // לוגיקת קניית רכוש
    void action(Player* player, Board* board) override; // מעודכן ללא פרמטר חלון
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    ~RailroadSquare();
};

#endif // RAILROADSQUARE_H
