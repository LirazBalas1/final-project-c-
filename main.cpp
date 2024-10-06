//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "GameController.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <csignal>
#include <string>

// מטפל אותות
void signalHandler(int signum) {
    std::cout << "\nInterrupt signal (" << signum << ") received. Cleaning up..." << std::endl;
    exit(signum);
}

// פונקציה לקבלת מספר שחקנים מהמשתמש דרך הטרמינל
int getNumberOfPlayers() {
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 8) {
        std::cout << "Enter number of players (1-8): ";
        std::cin >> numPlayers;
    }
    return numPlayers;
}

// פונקציה לקבלת מספר שחקני מחשב דרך הטרמינל
int getNumberOfAIPlayers(int maxPlayers) {
    int numAIPlayers = 0;
    while (numAIPlayers < 0 || numAIPlayers > maxPlayers) {
        std::cout << "Enter number of AI players (0-" << maxPlayers << "): ";
        std::cin >> numAIPlayers;
    }
    return numAIPlayers;
}

int main() {
    // רישום מטפל אותות
    signal(SIGINT, signalHandler);  // טיפול ב־Ctrl+C

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly");
    GameController* game = nullptr;

    try {
        game = new GameController();  // יצירת משחק חדש

        // קבלת מספר שחקנים אנושיים
        int numPlayers = getNumberOfPlayers(); 

        // קבלת מספר שחקני מחשב
        int numAIPlayers = getNumberOfAIPlayers(8 - numPlayers); 

        // אתחול המשחק עם מספר השחקנים הרגילים והממוחשבים
        game->initializeGame(numPlayers, numAIPlayers, window);  

        // לולאת משחק
        game->startGame(window);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }

    // ניקוי זיכרון במקרה של סגירה
    if (game != nullptr) {
        delete game;
        game = nullptr;
    }

    return 0;
}
