//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include "Square.hpp"
#include "PropertySquare.hpp"
#include "ChanceSquare.hpp"
#include "CommunityChestSquare.hpp"
#include "Card.hpp"
#include <SFML/Graphics.hpp>

class Board {
private:
    std::array<Square*, 40> squares;
    std::vector<Card*> chanceCards;
    std::vector<Card*> communityChestCards;
    sf::Font font;

    void initializeSquares();
    void initializeCards();
    void loadAssets();

public:
    Board();

    Square* getSquareAtPosition(int position);
    Card* drawChanceCard();
    Card* drawCommunityChestCard();

    void renderBoard(sf::RenderWindow& window);
    void auctionProperty(Square* property, std::vector<Player*>& players, sf::RenderWindow& window);

    std::vector<Square*> getPropertiesByColor(const sf::Color& color) const;

    ~Board();
};

#endif // BOARD_HPP