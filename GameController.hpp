//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <vector>
#include <deque>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.hpp"
#include "Board.hpp"
#include "Dice.hpp"

class GameController {
private:
    std::vector<std::unique_ptr<Player>> players;  // שימוש ב-unique_ptr עבור השחקנים
    Board board;
    Dice dice;
    int currentPlayerIndex;
    bool gameEnded;
    sf::Font font;
    int numberOfPlayers;  // מספר השחקנים שנבחר
    int aiPlayers;    

    // מערכת הודעות למשחק (מבוסס קונסול)
    std::deque<std::string> gameMessages;

    bool isAIPlayer(int playerIndex); // בדיקה אם השחקן הוא מחשב

public:
    GameController();
    ~GameController();

    void initializeGame(int numPlayers,int aiPlayers,sf::RenderWindow& window);  // אתחול משחק לפי מספר שחקנים
    void startGame(sf::RenderWindow& window);
    void playerTurn(Player* player, sf::RenderWindow& window);
    void removePlayer(Player* player);
    bool hasWinner() const;
    void aiPlayerTurn(Player* player, sf::RenderWindow& window);
    Player* getWinner() const;

    void renderGame(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window);

    // עדכונים והודעות בקונסול
    void logGameInfo(const std::string& info);
    void logPlayerStats();
    void displayMessages();  // מציג הודעות בקונסול

    // פונקציות חדשות
    void handleTrade(Player* player, sf::RenderWindow& window);  // טיפול בעסקאות
    void handleBuild(Player* player, sf::RenderWindow& window);  // טיפול בבנייה
};

#endif // GAMECONTROLLER_HPP
