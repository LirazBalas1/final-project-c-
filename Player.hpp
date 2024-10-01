//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Square;
class Board;
class RailroadSquare;  
class UtilitySquare;  
class PropertySquare;

class Player {
private:
    std::string name;
    int balance;
    int position;
    bool inJail;
    int jailTurns;
    std::vector<Square*> properties;
    sf::Color color;
    sf::CircleShape token;
    
public:
    Player(const std::string& playerName, int initialBalance, sf::Color playerColor);

    // Getters
    std::string getName() const;
    int getBalance() const;
    int getPosition() const;
    bool isInJail() const;
    sf::Color getColor() const;
    int getNumberOfRailroads() const;
    int getNumberOfUtilities() const;

    Square* selectPropertyToMortgage(sf::RenderWindow& window);
    void mortgage(Square* property, sf::RenderWindow& window);
    void declareBankruptcy(Player* creditor, sf::RenderWindow& window);
    void addProperty(Square* property) { properties.push_back(property); }
    int getTotalMortgageValue() const;

    // Setters
    void setBalance(int newBalance);
    void setPosition(int newPosition);

    // Actions
    void move(int steps, Board& board, sf::RenderWindow& window);
    void buyProperty(Square* property, sf::RenderWindow& window);
    void payRent(int amount, Player* owner, sf::RenderWindow& window);
    void addMoney(int amount, sf::RenderWindow& window);
    void sendToJail(sf::RenderWindow& window);
    void getOutOfJail();
    int rollDice();
    bool isBankrupt() const;
    void displayMessage(sf::RenderWindow& window, const std::string& message);

    // Rendering
    void render(sf::RenderWindow& window, const sf::Font& font) const;

    // Function to get only PropertySquare type properties
    std::vector<PropertySquare*> getPropertySquares() const;

    ~Player();
};

#endif // PLAYER_HPP