//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Dice.hpp"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <iostream>

Dice::Dice() : die1(0), die2(0), doublesCount(0) {
    // Initialize random seed
    std::srand(std::time(0));

    // Load the font for displaying the dice values
    if (!font.loadFromFile("Roboto-Black.ttf")) {
        std::cerr << "Error loading Roboto-Black.ttf! Default font will be used." << std::endl;
        // Consider loading a default font or using a placeholder for the text
    }

    // Set up the shapes for the dice
    die1Shape.setSize(sf::Vector2f(50.0f, 50.0f));
    die1Shape.setFillColor(sf::Color::White);
    die1Shape.setOutlineColor(sf::Color::Black);
    die1Shape.setOutlineThickness(2.0f);
    die1Shape.setPosition(100, 100);  // Example position

    die2Shape.setSize(sf::Vector2f(50.0f, 50.0f));
    die2Shape.setFillColor(sf::Color::White);
    die2Shape.setOutlineColor(sf::Color::Black);
    die2Shape.setOutlineThickness(2.0f);
    die2Shape.setPosition(160, 100);  // Example position, slightly offset

    // Set text properties
    die1Text.setFont(font);
    die1Text.setCharacterSize(24);
    die1Text.setFillColor(sf::Color::Black);
    die1Text.setPosition(die1Shape.getPosition().x + 15, die1Shape.getPosition().y + 10);

    die2Text.setFont(font);
    die2Text.setCharacterSize(24);
    die2Text.setFillColor(sf::Color::Black);
    die2Text.setPosition(die2Shape.getPosition().x + 15, die2Shape.getPosition().y + 10);
}

int Dice::roll() {
    die1 = (std::rand() % 6) + 1;
    die2 = (std::rand() % 6) + 1;

    if (die1 == die2) {
        doublesCount++;
    } else {
        doublesCount = 0;  // Reset doubles count if not a double
    }

    // Update the text objects with the new roll values
    die1Text.setString(std::to_string(die1));
    die2Text.setString(std::to_string(die2));

    return die1 + die2;  // Return the sum of both dice
}

void Dice::resetDoublesCount() {
    doublesCount = 0;
}

void Dice::render(sf::RenderWindow& window) {
    window.draw(die1Shape);
    window.draw(die2Shape);
    window.draw(die1Text);
    window.draw(die2Text);
}

int Dice::getDie1() const { return die1; }
int Dice::getDie2() const { return die2; }
int Dice::getTotal() const { return die1 + die2; }
bool Dice::isDouble() const { return die1 == die2; }
int Dice::getDoublesCount() const { return doublesCount; }
