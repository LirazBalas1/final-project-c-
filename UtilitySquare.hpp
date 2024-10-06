//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef UTILITYSQUARE_H
#define UTILITYSQUARE_H

#include "Square.hpp"
#include "Player.hpp"

class UtilitySquare : public Square {
private:
    int cost;              // עלות של השירות (Utility)
    Player* owner;         // הבעלים של השירות
    sf::Color color;
public:
    UtilitySquare(const std::string& name, int cost);
    sf::Color getColor() const override; // מימוש של הפונקציה

    // הפונקציה שמבצעת את הפעולה כשהשחקן נוחת על השירות
    void action(Player* player, Board* board) override;

    // הפונקציה שמציירת את השירות על הלוח
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    int getCost() const;  // החזרת עלות השירות
    int calculateRent(int diceRoll) const;  // חישוב שכר הדירה לפי תוצאת הקוביות
    void buyProperty(Player* player);  // רכישת השירות

    void setOwner(Player* newOwner) override { owner = newOwner; }  // הגדרת בעלים חדש
    Player* getOwner() const override { return owner; }  // החזרת הבעלים הנוכחי

    ~UtilitySquare();  // Destructor
};

#endif // UTILITYSQUARE_H
