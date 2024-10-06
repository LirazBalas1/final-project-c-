//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Square.hpp"

// Constructor initializes the square's name
Square::Square(const std::string& squareName) : name(squareName) {}

// Getter for the square's name
std::string Square::getName() const {
    return name;
}

// Virtual destructor to ensure cleanup in derived classes
Square::~Square() {}
