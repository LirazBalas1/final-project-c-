//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "Board.hpp"
#include "StreetSquare.hpp"
#include "RailroadSquare.hpp"
#include "UtilitySquare.hpp"
#include "SpecialSquare.hpp"
#include "ChanceSquare.hpp"
#include "CommunityChestSquare.hpp"
#include <iostream>

Board::Board() {
    loadAssets();
    initializeSquares();
    initializeCards();
}

void Board::loadAssets() {
    if (!font.loadFromFile("Roboto-Black.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
}

void Board::initializeSquares() {
    squares[0] = new SpecialSquare("GO");
    squares[1] = new StreetSquare("Mediterranean Avenue", 60, 2, sf::Color(150, 75, 0));
    squares[2] = new CommunityChestSquare();
    squares[3] = new StreetSquare("Baltic Avenue", 60, 4, sf::Color(150, 75, 0));
    squares[4] = new SpecialSquare("Income Tax");
    squares[5] = new RailroadSquare("Reading Railroad", 200);
    squares[6] = new StreetSquare("Oriental Avenue", 100, 6, sf::Color(135, 206, 235));
    squares[7] = new ChanceSquare();
    squares[8] = new StreetSquare("Vermont Avenue", 100, 6, sf::Color(135, 206, 235));
    squares[9] = new StreetSquare("Connecticut Avenue", 120, 8, sf::Color(135, 206, 235));
    squares[10] = new SpecialSquare("Jail");
    squares[11] = new StreetSquare("St. Charles Place", 140, 10, sf::Color(255, 0, 255));
    squares[12] = new UtilitySquare("Electric Company", 150);
    squares[13] = new StreetSquare("States Avenue", 140, 10, sf::Color(255, 0, 255));
    squares[14] = new StreetSquare("Virginia Avenue", 160, 12, sf::Color(255, 0, 255));
    squares[15] = new RailroadSquare("Pennsylvania Railroad", 200);
    squares[16] = new StreetSquare("St. James Place", 180, 14, sf::Color(255, 165, 0));
    squares[17] = new CommunityChestSquare();
    squares[18] = new StreetSquare("Tennessee Avenue", 180, 14, sf::Color(255, 165, 0));
    squares[19] = new StreetSquare("New York Avenue", 200, 16, sf::Color(255, 165, 0));
    squares[20] = new SpecialSquare("Free Parking");
    squares[21] = new StreetSquare("Kentucky Avenue", 220, 18, sf::Color(255, 0, 0));
    squares[22] = new ChanceSquare();
    squares[23] = new StreetSquare("Indiana Avenue", 220, 18, sf::Color(255, 0, 0));
    squares[24] = new StreetSquare("Illinois Avenue", 240, 20, sf::Color(255, 0, 0));
    squares[25] = new RailroadSquare("B. & O. Railroad", 200);
    squares[26] = new StreetSquare("Atlantic Avenue", 260, 22, sf::Color(255, 255, 0));
    squares[27] = new StreetSquare("Ventnor Avenue", 260, 22, sf::Color(255, 255, 0));
    squares[28] = new UtilitySquare("Water Works", 150);
    squares[29] = new StreetSquare("Marvin Gardens", 280, 24, sf::Color(255, 255, 0));
    squares[30] = new SpecialSquare("Go To Jail");
    squares[31] = new StreetSquare("Pacific Avenue", 300, 26, sf::Color(0, 255, 0));
    squares[32] = new StreetSquare("North Carolina Avenue", 300, 26, sf::Color(0, 255, 0));
    squares[33] = new CommunityChestSquare();
    squares[34] = new StreetSquare("Pennsylvania Avenue", 320, 28, sf::Color(0, 255, 0));
    squares[35] = new RailroadSquare("Short Line", 200);
    squares[36] = new ChanceSquare();
    squares[37] = new StreetSquare("Park Place", 350, 35, sf::Color(0, 0, 255));
    squares[38] = new SpecialSquare("Luxury Tax");
    squares[39] = new StreetSquare("Boardwalk", 400, 50, sf::Color(0, 0, 255));
}

void Board::initializeCards() {
    // Chance Cards
    chanceCards.push_back(new Card("Advance to Go (Collect $200)", 200));
    chanceCards.push_back(new Card("Advance to Illinois Ave—If you pass Go, collect $200", 0));
    chanceCards.push_back(new Card("Advance to St. Charles Place – If you pass Go, collect $200", 0));
    chanceCards.push_back(new Card("Advance token to nearest Utility. If unowned, you may buy it from the Bank. If owned, throw dice and pay owner a total 10 times the amount thrown.", 0));
    chanceCards.push_back(new Card("Advance token to the nearest Railroad and pay owner twice the rental to which he/she is otherwise entitled. If Railroad is unowned, you may buy it from the Bank.", 0));
    chanceCards.push_back(new Card("Bank pays you dividend of $50", 50));
    chanceCards.push_back(new Card("Get out of Jail Free", 0));
    chanceCards.push_back(new Card("Go Back 3 Spaces", 0));
    chanceCards.push_back(new Card("Go to Jail–Go directly to Jail–Do not pass Go, do not collect $200", 0));
    chanceCards.push_back(new Card("Make general repairs on all your property–For each house pay $25–For each hotel $100", -25));
    chanceCards.push_back(new Card("Pay poor tax of $15", -15));
    chanceCards.push_back(new Card("Take a trip to Reading Railroad–If you pass Go, collect $200", 0));
    chanceCards.push_back(new Card("Take a walk on the Boardwalk–Advance token to Boardwalk", 0));
    chanceCards.push_back(new Card("You have been elected Chairman of the Board–Pay each player $50", -50));
    chanceCards.push_back(new Card("Your building and loan matures—Collect $150", 150));
    chanceCards.push_back(new Card("You have won a crossword competition—Collect $100", 100));

    // Community Chest Cards
    communityChestCards.push_back(new Card("Advance to Go (Collect $200)", 200));
    communityChestCards.push_back(new Card("Bank error in your favor—Collect $200", 200));
    communityChestCards.push_back(new Card("Doctor's fee—Pay $50", -50));
    communityChestCards.push_back(new Card("From sale of stock you get $50", 50));
    communityChestCards.push_back(new Card("Get Out of Jail Free", 0));
    communityChestCards.push_back(new Card("Go to Jail–Go directly to jail–Do not pass Go–Do not collect $200", 0));
    communityChestCards.push_back(new Card("Grand Opera Night—Collect $50 from every player for opening night seats", 50));
    communityChestCards.push_back(new Card("Holiday Fund matures—Receive $100", 100));
    communityChestCards.push_back(new Card("Income tax refund–Collect $20", 20));
    communityChestCards.push_back(new Card("Life insurance matures–Collect $100", 100));
    communityChestCards.push_back(new Card("Pay hospital fees of $100", -100));
    communityChestCards.push_back(new Card("Pay school fees of $150", -150));
    communityChestCards.push_back(new Card("Receive $25 consultancy fee", 25));
    communityChestCards.push_back(new Card("You are assessed for street repairs–$40 per house–$115 per hotel", -40));
    communityChestCards.push_back(new Card("You have won second prize in a beauty contest–Collect $10", 10));
    communityChestCards.push_back(new Card("You inherit $100", 100));
}

Square* Board::getSquareAtPosition(int position) {
    if (position >= 0 && position < 40) {
        return squares[position];
    }
    return nullptr;
}

Card* Board::drawChanceCard() {
    if (!chanceCards.empty()) {
        Card* card = chanceCards.back();
        chanceCards.pop_back();
        chanceCards.insert(chanceCards.begin(), card);
        return card;
    }
    return nullptr;
}

Card* Board::drawCommunityChestCard() {
    if (!communityChestCards.empty()) {
        Card* card = communityChestCards.back();
        communityChestCards.pop_back();
        communityChestCards.insert(communityChestCards.begin(), card);
        return card;
    }
    return nullptr;
}

void Board::renderBoard(sf::RenderWindow& window) {
    // Clear the window with white color
    window.clear(sf::Color::White);

    // Define board dimensions
    const float boardSize = 800.f;
    const float squareSize = boardSize / 11;  // 11 squares per side
    const sf::Vector2f boardPosition(50.f, 50.f);  // Offset from window edge

    // Draw board outline
    sf::RectangleShape boardOutline(sf::Vector2f(boardSize, boardSize));
    boardOutline.setPosition(boardPosition);
    boardOutline.setFillColor(sf::Color::Transparent);
    boardOutline.setOutlineColor(sf::Color::Black);
    boardOutline.setOutlineThickness(2.f);
    window.draw(boardOutline);

    // Render each square
    for (int i = 0; i < 40; ++i) {
        sf::Vector2f position;
        if (i < 10) {
            position = sf::Vector2f(boardPosition.x + boardSize - (i + 1) * squareSize, boardPosition.y + boardSize - squareSize);
        } else if (i < 20) {
            position = sf::Vector2f(boardPosition.x, boardPosition.y + boardSize - (i - 8) * squareSize);
        } else if (i < 30) {
            position = sf::Vector2f(boardPosition.x + (i - 20) * squareSize, boardPosition.y);
        } else {
            position = sf::Vector2f(boardPosition.x + boardSize - squareSize, boardPosition.y + (i - 30) * squareSize);
        }
        
        squares[i]->render(window, position, squareSize, font);
    }
}

void Board::auctionProperty(Square* property, std::vector<Player*>& players, sf::RenderWindow& window) {
    // Implement auction logic here
}
std::vector<Square*> Board::getPropertiesByColor(const sf::Color& color) const {
    std::vector<Square*> properties;
    for (auto square : squares) {
        if (auto streetSquare = dynamic_cast<StreetSquare*>(square)) {
            if (streetSquare->getColor() == color) {
                properties.push_back(square);
            }
        }
    }
    return properties;
}

Board::~Board() {
    for (auto square : squares) {
        delete square;
    }
    for (auto card : chanceCards) {
        delete card;
    }
    for (auto card : communityChestCards) {
        delete card;
    }
}