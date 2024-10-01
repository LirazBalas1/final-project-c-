//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Square.hpp"

Square::Square(const std::string& squareName) : name(squareName) {}

std::string Square::getName() const {
    return name;
}

Square::~Square() {}