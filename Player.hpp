//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>  // לשימוש ב-Smart Pointers

class Square;
class Board;
class PropertySquare;
class RailroadSquare;
class UtilitySquare;

class Player {
private:
    std::string name;
    int balance;
    int position;
    bool inJail;
    int jailTurns;
    std::vector<std::unique_ptr<Square>> properties;  // שינוי לשימוש ב-Smart Pointers
    sf::Color color;
    sf::CircleShape token;
    int amount;
    int interestRate;
    bool isAI;  // שדה חדש לזיהוי האם השחקן הוא AI, מעבירים אותו אחרי הצבע (color)

public:
    Player(const std::string& playerName, int initialBalance, sf::Color playerColor, bool isAI);
    void takeAITurn(Board& board);
    std::string getName() const;
    int getBalance() const;
    int getPosition() const;
    bool isInJail() const;
    bool isAIPlayer() const;  // פונקציה חדשה לזיהוי שחקן AI 
    bool tryToEscapeJail();  // פונקציה שמנסה להוציא את השחקן מהכלא
    sf::Color getColor() const;
    int getNumberOfRailroads() const;
    int getNumberOfUtilities() const;
    void forfeit();
    void setBalance(int newBalance);
    void setPosition(int newPosition);
    void move(int roll, Board& board);
    int getJailTurns() const;
    void incrementJailTurn();
    void buyProperty(Square* property);
    void payRent(int amount, Player* owner);
    void addMoney(int amount);
    void sendToJail();
    void getOutOfJail();
    int rollDice();
    bool isBankrupt() const;
    int getTotalMortgageValue() const;
    void removeProperty(Square* property);
    void offerLoan(Player* otherPlayer, int amount, int interestRate);
    void repayLoan(int amount, Player* lender);

    void addProperty(std::unique_ptr<Square> property);  // שינוי לשימוש ב-Smart Pointers
    std::vector<PropertySquare*> getPropertySquares() const;
    void displayMessage(const std::string& message);

    void render(sf::RenderWindow& window, const sf::Font& font) const;
    ~Player();  // משחרר זיכרון
};

#endif // PLAYER_HPP
