//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "GameController.hpp"
#include "PropertySquare.hpp"
#include "Player.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

GameController::GameController() : currentPlayerIndex(0), gameEnded(false) {
    if (!font.loadFromFile("Roboto-Black.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
}

void GameController::initializeGame(int numPlayers) {
    players.clear();
    std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow,
                                     sf::Color::Magenta, sf::Color::Cyan, sf::Color::White, sf::Color::Black};
    
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(new Player("Player " + std::to_string(i+1), 1500, colors[i]));
    }
}
void GameController::startGame(sf::RenderWindow& window) {
    while (window.isOpen()) {
        handleEvents(window);
        
        if (!gameEnded) {
            Player* currentPlayer = players[currentPlayerIndex];
            playerTurn(currentPlayer, window);
            
            if (hasWinner()) {
                gameEnded = true;
                Player* winner = getWinner();
                std::string winMessage = "Game Over! " + winner->getName() + " wins!";
                std::cout << winMessage << std::endl;
                addGameMessage(winMessage);
            } else {
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            }
        }
        
        renderGame(window);
        
        // אם המשחק הסתיים, נציג הודעה ונחכה ללחיצת כפתור
        if (gameEnded) {
            sf::Text endGameText("Game Over! Press any key to exit.", font, 30);
            endGameText.setPosition(200, 300);
            endGameText.setFillColor(sf::Color::Red);
            window.draw(endGameText);
            window.display();
            
            sf::Event event;
            while (window.waitEvent(event)) {
                if (event.type == sf::Event::KeyPressed || 
                    event.type == sf::Event::MouseButtonPressed ||
                    event.type == sf::Event::Closed) {
                    return;
                }
            }
        }
    }
}
void GameController::playerTurn(Player* player, sf::RenderWindow& window) {
    std::cout << player->getName() << "'s turn" << std::endl;
    
    int roll = dice.roll();
    std::cout << player->getName() << " rolled a " << roll << std::endl;
    
    // הוספת השהייה אחרי הטלת הקוביות
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    player->move(roll, board, window);
    
    addGameMessage(player->getName() + " rolled a " + std::to_string(roll));

    // הוספת השהייה בסוף התור
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void GameController::removePlayer(Player* player) {
    auto it = std::find(players.begin(), players.end(), player);
    if (it != players.end()) {
        players.erase(it);
        delete player;
    }
}

bool GameController::hasWinner() const {
    return players.size() == 1 || std::any_of(players.begin(), players.end(), 
        [](const Player* p) { return p->getBalance() >= 2000; });
}

Player* GameController::getWinner() const {
    if (players.size() == 1) {
        return players[0];
    }
    auto it = std::max_element(players.begin(), players.end(), 
        [](const Player* a, const Player* b) { return a->getBalance() < b->getBalance(); });
    return *it;
}

// New methods for player stats and game messages
void GameController::renderPlayerStats(sf::RenderWindow& window) {
    for (size_t i = 0; i < players.size(); ++i) {
        sf::Text stats;
        stats.setFont(font);
        stats.setCharacterSize(18);
        stats.setFillColor(sf::Color::Black);  // Changed to black for better visibility on white background
        stats.setPosition(10, 10 + (i * 50));  // Adjust position dynamically

        std::string statsStr = players[i]->getName() + "\nBalance: $" + std::to_string(players[i]->getBalance()) + "\nProperties: ";
        for (const auto& property : players[i]->getPropertySquares()) {
            statsStr += property->getName() + ", ";
        }
        if (!statsStr.empty()) {
            statsStr.pop_back();  // Remove the last comma
            statsStr.pop_back();  // Remove the last space
        }
        stats.setString(statsStr);
        window.draw(stats);
    }
}

void GameController::addGameMessage(const std::string& message) {
    gameMessages.push_back(message);
    if (gameMessages.size() > 5) {  // Limit number of messages shown
        gameMessages.pop_front();  // Remove old messages
    }
}

void GameController::renderGameMessages(sf::RenderWindow& window) {
    int yOffset = window.getSize().y - 100;  // Bottom of the screen
    for (const auto& message : gameMessages) {
        sf::Text messageText;
        messageText.setFont(font);
        messageText.setCharacterSize(16);
        messageText.setFillColor(sf::Color::Yellow);
        messageText.setPosition(10, yOffset);

        messageText.setString(message);
        window.draw(messageText);

        yOffset -= 20;  // Move up for the next message
    }
}
void GameController::renderGameInfo(sf::RenderWindow& window) {
    sf::Text gameInfo;
    gameInfo.setFont(font);
    gameInfo.setCharacterSize(20);
    gameInfo.setFillColor(sf::Color::Black);
    gameInfo.setPosition(10, 10);

    std::string info = "Current Player: " + players[currentPlayerIndex]->getName() + "\n";
    info += "Balance: $" + std::to_string(players[currentPlayerIndex]->getBalance()) + "\n";
    
    info += "\nProperties Owned:\n";
    const auto& currentPlayerProperties = players[currentPlayerIndex]->getPropertySquares();
    if (currentPlayerProperties.empty()) {
        info += "None\n";
    } else {
        for (const auto& property : currentPlayerProperties) {
            info += "- " + property->getName() + "\n";
        }
    }

    gameInfo.setString(info);
    window.draw(gameInfo);
}

void GameController::renderGame(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    
    board.renderBoard(window);
    
    for (const auto& player : players) {
        player->render(window, font);
    }

    renderGameInfo(window);
    renderPlayerStats(window);
    renderGameMessages(window);

    window.display();
}

void GameController::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Add more event handling here
    }
}

GameController::~GameController() {
    for (auto player : players) {
        delete player;
    }
}
