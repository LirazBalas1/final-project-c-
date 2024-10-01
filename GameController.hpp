//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Board.hpp"
#include "Dice.hpp"
#include <deque>  // For message system

class GameController {
private:
    std::vector<Player*> players;
    Board board;
    Dice dice;
    int currentPlayerIndex;
    bool gameEnded;
    sf::Font font;

    // New additions
    std::deque<std::string> gameMessages;  // Stores game messages
    std::vector<PropertySquare*> properties;  // Add this to hold the player's properties

public:
    GameController();

    void initializeGame(int numPlayers);
    void startGame(sf::RenderWindow& window);
    void playerTurn(Player* player, sf::RenderWindow& window);
    void removePlayer(Player* player);
    bool hasWinner() const;
    Player* getWinner() const;
    void renderGame(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window);

    // New methods for stats and messages
    void renderPlayerStats(sf::RenderWindow& window);
    void addGameMessage(const std::string& message);
    void renderGameMessages(sf::RenderWindow& window);
    void renderGameInfo(sf::RenderWindow& window);
    

    ~GameController();
};

#endif // GAMECONTROLLER_HPP
