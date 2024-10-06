//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef PROPERTYSQUARE_HPP
#define PROPERTYSQUARE_HPP

#include "Square.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class PropertySquare : public Square {
private:
    int cost;               // עלות הנכס
    int baseRent;           // שכר דירה בסיסי ללא בתים או בתי מלון
    Player* owner;          // הבעלים של הנכס
    int houses;             // מספר הבתים שנבנו בנכס
    int hotels;             // מספר בתי המלון בנכס
    bool mortgaged;         // האם הנכס נמצא במשכנתא
    int mortgageValue;      // ערך המשכנתא
    sf::Color color;        // צבע הנכס (לקבוצות צבעוניות במשחק)

public:
    PropertySquare(const std::string& propertyName, int propertyCost, int propertyRent, const sf::Color& propertyColor);

    sf::Color getColor() const override ;// אפור }  // מימוש של הפונקציה
    // Getters
    int getCost() const;
    int getBaseRent() const;

    int getMortgageValue() const; 
    bool isMortgaged() const; 
    void setMortgaged(bool mortgaged); 
    void setOwner(Player* newOwner); 
    Player* getOwner() const; 

    // פעולות עם הנכס
    void buyProperty(Player* player);    
    int calculateRent() const;           
    void buildHouse();                    
    void buildHotel();                    

    bool canBuildHouse() const;           
    bool canBuildHotel() const;           

    // הפונקציה Action להפעיל את הפעולה כשהשחקן מגיע לנכס
    void action(Player* player, Board* board) override;
    void render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) override;

    // Destructor
    ~PropertySquare();
};

#endif // PROPERTYSQUARE_HPP
