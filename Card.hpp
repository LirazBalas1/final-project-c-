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
    std::string description;
    int amount;

public:
    Card(const std::string& desc, int amt);

    std::string getDescription() const;
    int getAmount() const;

    void applyToPlayer(Player* player, Board* board, sf::RenderWindow& window);
    void render(sf::RenderWindow& window, const sf::Font& font) const;
};

#endif // CARD_HPP