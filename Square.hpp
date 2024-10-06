//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class Player;
class Board;

class Square {
protected:
    std::string name;  // שם המשבצת

public:
    // Constructor
    Square(const std::string& squareName);

     virtual sf::Color getColor() const = 0; // פונקציה וירטואלית טהורה לקבלת הצבע

    // Pure virtual functions (abstract class)
    virtual void action(Player* player, Board* board) = 0;  // פונקציה לפעולה של השחקן במשבצת
    virtual void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) = 0;  // פונקציה לרינדור

    // Virtual ownership-related methods with default behavior
    virtual void setOwner(Player* newOwner) {}  // הגדרת בעל המשבצת, ברירת מחדל שלא עושה כלום
    virtual Player* getOwner() const { return nullptr; }  // החזרת הבעלים, ברירת מחדל מחזיר nullptr

    // Mortgage-related methods with default behavior
    virtual int getMortgageValue() const { return 0; }  // ערך משכנתא ברירת מחדל 0
    virtual bool isMortgaged() const { return false; }  // ברירת מחדל שהמשבצת לא ממושכנת
    virtual void setMortgaged(bool mortgaged) {}  // פונקציה שמגדירה אם המשבצת ממושכנת

    // Getter for the square's name
    std::string getName() const;

    // Virtual destructor to ensure proper cleanup
    virtual ~Square();
};

#endif // SQUARE_H
