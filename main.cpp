//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "GameController.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
int getNumberOfPlayers(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Roboto-Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return 2;
    }

    sf::Text questionText("Enter number of players (2-8):", font, 20);
    questionText.setPosition(200, 200);

    sf::Text inputText("", font, 20);
    inputText.setPosition(200, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '2' && event.text.unicode <= '8') {
                    return event.text.unicode - '0';
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(questionText);
        window.draw(inputText);
        window.display();
    }

    return 2;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Monopoly");
    GameController game;

    int numPlayers = getNumberOfPlayers(window);
    game.initializeGame(numPlayers);
    game.startGame(window);

    return 0;
}