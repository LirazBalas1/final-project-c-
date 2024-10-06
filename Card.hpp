//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Player;
class Board;

class Card {
private:
    std::string description;  // תיאור הקלף
    int amount;               // סכום הכסף או השפעה אחרת של הקלף (0 עבור פעולות מיוחדות)

public:
    Card(const std::string& desc, int amt);

    // מחזיר את התיאור של הקלף
    std::string getDescription() const;

    // מחזיר את הסכום של הקלף
    int getAmount() const;

    // הפעלת הקלף על שחקן
    void applyToPlayer(Player* player, Board* board);

    // פונקציה לציור גרפי של הקלף
    void render(sf::RenderWindow& window, const sf::Font& font) const;
};

#endif // CARD_HPP
