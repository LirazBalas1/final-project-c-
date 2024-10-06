//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <memory>  // for std::unique_ptr
#include "Square.hpp"
#include "PropertySquare.hpp"
#include "ChanceSquare.hpp"
#include "CommunityChestSquare.hpp"
#include "Card.hpp"
#include "Dice.hpp"
#include <SFML/Graphics.hpp>

class Board {
private:
    std::array<std::unique_ptr<Square>, 40> squares;  // שימוש ב-unique_ptr כדי לנהל זיכרון
    std::vector<std::unique_ptr<Card>> chanceCards;   // קלפי סיכוי
    std::vector<std::unique_ptr<Card>> communityChestCards;  // קלפי תיבת קהילה
    Dice dice;  // משתנה לקוביות
    sf::Font font;
    bool freeParkingRuleEnabled;
    bool exactLanding;

    void initializeSquares();
    void initializeCards();
    void loadAssets();

public:
    Board();
    ~Board() = default;  // היות שאנחנו משתמשים ב-unique_ptr, לא צריך כעת לפנות זיכרון ידנית

    Square* getSquareAtPosition(int position);
    Card* drawChanceCard();
    Card* drawCommunityChestCard();
    Dice& getDice();
    void applyFreeParkingRule(Player* player);
    void applyGoRule(Player* player, bool exactLanding);

    void renderBoard(sf::RenderWindow& window);
    void auctionProperty(Square* property, std::vector<Player*>& players, sf::RenderWindow& window);

    std::vector<Square*> getPropertiesByColor(const sf::Color& color) const;
};

#endif // BOARD_HPP
