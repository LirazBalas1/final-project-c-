//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Dice.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Dice::Dice() : die1(0), die2(0), doublesCount(0) {
    // Seed for random number generation
    std::srand(std::time(0));

    // Load the font for displaying the dice values
    if (!font.loadFromFile("Roboto-Black.ttf")) {
        std::cerr << "Error loading Roboto-Black.ttf!" << std::endl;
    }

    // Set up die1 shape (for visual dice rendering)
    die1Shape.setSize(sf::Vector2f(50.0f, 50.0f));  // Size of the dice
    die1Shape.setFillColor(sf::Color::White);       // Color of the dice
    die1Shape.setOutlineColor(sf::Color::Black);    // Outline color
    die1Shape.setOutlineThickness(2.0f);            // Outline thickness
    die1Shape.setPosition(100, 100);                // Position on the window

    // Set up die2 shape
    die2Shape.setSize(sf::Vector2f(50.0f, 50.0f));
    die2Shape.setFillColor(sf::Color::White);
    die2Shape.setOutlineColor(sf::Color::Black);
    die2Shape.setOutlineThickness(2.0f);
    die2Shape.setPosition(160, 100);  // Slightly offset from die1

    // Set up die1 text (for displaying dice values)
    die1Text.setFont(font);
    die1Text.setCharacterSize(24);
    die1Text.setFillColor(sf::Color::Black);
    die1Text.setPosition(die1Shape.getPosition().x + 20, die1Shape.getPosition().y + 10);  // Centered in the die

    // Set up die2 text
    die2Text.setFont(font);
    die2Text.setCharacterSize(24);
    die2Text.setFillColor(sf::Color::Black);
    die2Text.setPosition(die2Shape.getPosition().x + 20, die2Shape.getPosition().y + 10);
}
void Dice::setTotal(int newTotal) {
    total = newTotal;
    // Optionally, you can set die1 and die2 to values that sum up to total
    die1 = newTotal / 2;
    die2 = newTotal - die1;
}

int Dice::roll() {
    if (total != 0) {
        int result = total;
        total = 0;  // Reset the total after using it
        die1 = result / 2;
        die2 = result - die1;
    } else {
        die1 = (std::rand() % 6) + 1;
        die2 = (std::rand() % 6) + 1;
    }

    // Check for doubles
    if (die1 == die2) {
        doublesCount++;
    } else {
        doublesCount = 0;  // Reset if not a double
    }

    // Update the dice values visually
    die1Text.setString(std::to_string(die1));
    die2Text.setString(std::to_string(die2));

    return die1 + die2;  // Return the total dice value
}

int Dice::getDie1() const {
    return die1;
}

int Dice::getDie2() const {
    return die2;
}

int Dice::getTotal() const {
    return die1 + die2;
}

bool Dice::isDouble() const {
    return die1 == die2;
}

int Dice::getDoublesCount() const {
    return doublesCount;
}

void Dice::resetDoublesCount() {
    doublesCount = 0;
}

// Render the dice visually in the window
void Dice::render(sf::RenderWindow& window) {
    // Draw the dice shapes and their respective values
    window.draw(die1Shape);
    window.draw(die2Shape);
    window.draw(die1Text);
    window.draw(die2Text);
}
