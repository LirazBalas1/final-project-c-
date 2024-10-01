//Liraz Balas
//211801220
//lbalad13@gmail.com
#ifndef PROPERTYSQUARE_H
#define PROPERTYSQUARE_H

#include "Square.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class PropertySquare : public Square {
private:
    int cost;               // Cost of the property
    int baseRent;           // Base rent without houses or hotels
    Player* owner;          // Owner of the property
    int houses;             // Number of houses on the property
    int hotels;             // Number of hotels on the property
    bool mortgaged;
    int mortgageValue;

public:
    PropertySquare(const std::string& propertyName, int propertyCost, int propertyRent);

    // Getters
    int getCost() const;
    int getBaseRent() const;

    int getMortgageValue() const override { return mortgageValue; };
    bool isMortgaged() const override { return mortgaged; };
    void setMortgaged(bool mortgaged) override { this->mortgaged = mortgaged; };
    void setOwner(Player* newOwner) override { owner = newOwner; }
    Player* getOwner() const override { return owner; }
    // Setters

    // Property actions
    void buyProperty(Player* player, sf::RenderWindow& window);     // Buy property
    int calculateRent() const;            // Calculate the rent
    void buildHouse();                    // Build a house (for streets)
    void buildHotel();                    // Build a hotel (for streets)

    bool canBuildHouse() const;           // Check if a house can be built
    bool canBuildHotel() const;           // Check if a hotel can be built

    // Override Square's action method to take Player and Board as parameters
    void action(Player* player, Board* board, sf::RenderWindow& window) override;

    // Destructor
    ~PropertySquare();
};

#endif // PROPERTYSQUARE_H
