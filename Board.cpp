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
        std::cerr << "Failed to load font Roboto-Black.ttf!" << std::endl;
    } else {
        std::cout << "Font loaded successfully." << std::endl;
    }
}
void Board::initializeSquares() {
    // Example initialization of squares using unique_ptr
    squares[0] = std::make_unique<SpecialSquare>("GO");
    squares[1] = std::make_unique<StreetSquare>("Mediterranean Avenue", 60, 2, sf::Color(150, 75, 0)); // צבע חום
    squares[2] = std::make_unique<CommunityChestSquare>();
    squares[3] = std::make_unique<StreetSquare>("Baltic Avenue", 60, 4, sf::Color(150, 75, 0)); // צבע חום
    squares[4] = std::make_unique<SpecialSquare>("Income Tax");
    squares[5] = std::make_unique<RailroadSquare>("Reading Railroad", 200);
    squares[6] = std::make_unique<StreetSquare>("Oriental Avenue", 100, 6, sf::Color(135, 206, 235)); // צבע תכלת
    squares[7] = std::make_unique<ChanceSquare>();
    squares[8] = std::make_unique<StreetSquare>("Vermont Avenue", 100, 6, sf::Color(135, 206, 235)); // צבע תכלת
    squares[9] = std::make_unique<StreetSquare>("Connecticut Avenue", 120, 8, sf::Color(135, 206, 235)); // צבע תכלת
    squares[10] = std::make_unique<SpecialSquare>("Jail");
    squares[11] = std::make_unique<StreetSquare>("St. Charles Place", 140, 10, sf::Color(255, 0, 255)); // צבע ורוד
    squares[12] = std::make_unique<UtilitySquare>("Electric Company", 150);
    squares[13] = std::make_unique<StreetSquare>("States Avenue", 140, 10, sf::Color(255, 0, 255)); // צבע ורוד
    squares[14] = std::make_unique<StreetSquare>("Virginia Avenue", 160, 12, sf::Color(255, 0, 255)); // צבע ורוד
    squares[15] = std::make_unique<RailroadSquare>("Pennsylvania Railroad", 200);
    squares[16] = std::make_unique<StreetSquare>("St. James Place", 180, 14, sf::Color(255, 165, 0)); // צבע כתום
    squares[17] = std::make_unique<CommunityChestSquare>();
    squares[18] = std::make_unique<StreetSquare>("Tennessee Avenue", 180, 14, sf::Color(255, 165, 0)); // צבע כתום
    squares[19] = std::make_unique<StreetSquare>("New York Avenue", 200, 16, sf::Color(255, 165, 0)); // צבע כתום
    squares[20] = std::make_unique<SpecialSquare>("Free Parking");
    squares[21] = std::make_unique<StreetSquare>("Kentucky Avenue", 220, 18, sf::Color(255, 0, 0)); // צבע אדום
    squares[22] = std::make_unique<ChanceSquare>();
    squares[23] = std::make_unique<StreetSquare>("Indiana Avenue", 220, 18, sf::Color(255, 0, 0)); // צבע אדום
    squares[24] = std::make_unique<StreetSquare>("Illinois Avenue", 240, 20, sf::Color(255, 0, 0)); // צבע אדום
    squares[25] = std::make_unique<RailroadSquare>("B. & O. Railroad", 200);
    squares[26] = std::make_unique<StreetSquare>("Atlantic Avenue", 260, 22, sf::Color(255, 255, 0)); // צבע צהוב
    squares[27] = std::make_unique<StreetSquare>("Ventnor Avenue", 260, 22, sf::Color(255, 255, 0)); // צבע צהוב
    squares[28] = std::make_unique<UtilitySquare>("Water Works", 150);
    squares[29] = std::make_unique<StreetSquare>("Marvin Gardens", 280, 24, sf::Color(255, 255, 0)); // צבע צהוב
    squares[30] = std::make_unique<SpecialSquare>("Go To Jail");
    squares[31] = std::make_unique<StreetSquare>("Pacific Avenue", 300, 26, sf::Color(0, 255, 0)); // צבע ירוק
    squares[32] = std::make_unique<StreetSquare>("North Carolina Avenue", 300, 26, sf::Color(0, 255, 0)); // צבע ירוק
    squares[33] = std::make_unique<CommunityChestSquare>();
    squares[34] = std::make_unique<StreetSquare>("Pennsylvania Avenue", 320, 28, sf::Color(0, 255, 0)); // צבע ירוק
    squares[35] = std::make_unique<RailroadSquare>("Short Line", 200);
    squares[36] = std::make_unique<ChanceSquare>();
    squares[37] = std::make_unique<StreetSquare>("Park Place", 350, 35, sf::Color(0, 0, 255)); // צבע כחול כהה
    squares[38] = std::make_unique<SpecialSquare>("Luxury Tax");
    squares[39] = std::make_unique<StreetSquare>("Boardwalk", 400, 50, sf::Color(0, 0, 255)); // צבע כחול כהה
}


void Board::initializeCards() {
    chanceCards.push_back(std::make_unique<Card>("Advance to Go (Collect $200)", 200));
    chanceCards.push_back(std::make_unique<Card>("Advance to Illinois Ave—If you pass Go, collect $200", 0));
    chanceCards.push_back(std::make_unique<Card>("Advance to St. Charles Place – If you pass Go, collect $200", 0));
    chanceCards.push_back(std::make_unique<Card>("Advance token to nearest Utility. If unowned, you may buy it from the Bank. If owned, throw dice and pay owner 10 times the amount thrown.", 0));
    chanceCards.push_back(std::make_unique<Card>("Advance token to the nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental.", 0));
    chanceCards.push_back(std::make_unique<Card>("Bank pays you dividend of $50", 50));
    chanceCards.push_back(std::make_unique<Card>("Get out of Jail Free", 0));
    chanceCards.push_back(std::make_unique<Card>("Go Back 3 Spaces", 0));
    chanceCards.push_back(std::make_unique<Card>("Go directly to Jail—Do not pass Go, do not collect $200", 0));
    chanceCards.push_back(std::make_unique<Card>("Make general repairs on all your property—For each house pay $25, for each hotel $100", -25));
    chanceCards.push_back(std::make_unique<Card>("Pay poor tax of $15", -15));
    chanceCards.push_back(std::make_unique<Card>("Take a trip to Reading Railroad—If you pass Go, collect $200", 0));
    chanceCards.push_back(std::make_unique<Card>("Take a walk on the Boardwalk—Advance token to Boardwalk", 0));
    chanceCards.push_back(std::make_unique<Card>("You have been elected Chairman of the Board—Pay each player $50", -50));
    chanceCards.push_back(std::make_unique<Card>("Your building and loan matures—Collect $150", 150));
    chanceCards.push_back(std::make_unique<Card>("You have won a crossword competition—Collect $100", 100));

    communityChestCards.push_back(std::make_unique<Card>("Advance to Go (Collect $200)", 200));
    communityChestCards.push_back(std::make_unique<Card>("Bank error in your favor—Collect $200", 200));
    communityChestCards.push_back(std::make_unique<Card>("Doctor's fees—Pay $50", -50));
    communityChestCards.push_back(std::make_unique<Card>("From sale of stock you get $50", 50));
    communityChestCards.push_back(std::make_unique<Card>("Get Out of Jail Free", 0));
    communityChestCards.push_back(std::make_unique<Card>("Go directly to Jail—Do not pass Go, do not collect $200", 0));
    communityChestCards.push_back(std::make_unique<Card>("Grand Opera Night—Collect $50 from every player for opening night seats", 50));
    communityChestCards.push_back(std::make_unique<Card>("Holiday Fund matures—Receive $100", 100));
    communityChestCards.push_back(std::make_unique<Card>("Income tax refund—Collect $20", 20));
    communityChestCards.push_back(std::make_unique<Card>("Life insurance matures—Collect $100", 100));
    communityChestCards.push_back(std::make_unique<Card>("Pay hospital fees of $100", -100));
    communityChestCards.push_back(std::make_unique<Card>("Pay school fees of $150", -150));
    communityChestCards.push_back(std::make_unique<Card>("Receive $25 consultancy fee", 25));
    communityChestCards.push_back(std::make_unique<Card>("You are assessed for street repairs—$40 per house, $115 per hotel", -40));
    communityChestCards.push_back(std::make_unique<Card>("You have won second prize in a beauty contest—Collect $10", 10));
    communityChestCards.push_back(std::make_unique<Card>("You inherit $100", 100));

    std::cout << "Initialized game cards." << std::endl;
}

Square* Board::getSquareAtPosition(int position) {
    if (position >= 0 && position < static_cast<int>(squares.size())) {
        return squares[position].get();
    }
    return nullptr;
}

Card* Board::drawChanceCard() {
    if (!chanceCards.empty()) {
        Card* card = chanceCards.back().get();
        chanceCards.pop_back();
        chanceCards.insert(chanceCards.begin(), std::make_unique<Card>(*card));  // Move drawn card to the front
        std::cout << "Chance card drawn: " << card->getDescription() << std::endl;
        return card;
    }
    return nullptr;
}

Card* Board::drawCommunityChestCard() {
    std::cout << "Attempting to draw a Community Chest card." << std::endl;

    if (!communityChestCards.empty()) {
        Card* card = communityChestCards.back().get();
        communityChestCards.pop_back();
        communityChestCards.insert(communityChestCards.begin(), std::make_unique<Card>(*card));  // Move drawn card to the front
        std::cout << "Community Chest card drawn: " << card->getDescription() << std::endl;
        return card;
    }

    std::cout << "No Community Chest cards left!" << std::endl;
    return nullptr;
}


void Board::applyFreeParkingRule(Player* player) {
    if (freeParkingRuleEnabled) {
        int reward = 400;  // ניתן לקבוע סכום קבוע או מבוסס על כסף שהצטבר
        player->addMoney(reward);
        player->displayMessage(player->getName() + " received $" + std::to_string(reward) + " for landing on Free Parking.");
    }
}

void Board::applyGoRule(Player* player, bool exactLanding) {
    int reward = exactLanding ? 400 : 200;  // קבל יותר כסף אם נחת בדיוק
    player->addMoney(reward);
    player->displayMessage(player->getName() + " received $" + std::to_string(reward) + " for passing or landing on Go.");
}

void Board::renderBoard(sf::RenderWindow& window) {
    const int totalSquares = 40; // כמות המשבצות הכוללת
    const float boardWidth = window.getSize().x;
    const float boardHeight = window.getSize().y;
    const float sideLength = boardWidth / 11; // הגודל של כל משבצת בשוליים, מניחים שהלוח ריבועי עם חמישה משבצות בכל צד
    const sf::Vector2f topRightCorner(boardWidth - sideLength, 0);
    const sf::Vector2f bottomLeftCorner(0, boardHeight - sideLength);

    window.clear(sf::Color::White);

    // נקבע את המיקום והצבע של כל משבצת בהתאם למיקומה בלוח
    for (int i = 0; i < totalSquares; ++i) {
        sf::RectangleShape square(sf::Vector2f(sideLength, sideLength));
        sf::Text squareText(squares[i]->getName(), font, 14);
        squareText.setFillColor(sf::Color::Black);

        float x = 0, y = 0;
        // קביעת מיקום המשבצת
        if (i < 10) {
            x = i * sideLength;
            y = boardHeight - sideLength;
        } else if (i < 20) {
            x = boardWidth - sideLength;
            y = boardHeight - (i - 9) * sideLength - sideLength;
        } else if (i < 30) {
            x = boardWidth - (i - 19) * sideLength - sideLength;
            y = 0;
        } else {
            x = 0;
            y = (i - 29) * sideLength;
        }

        square.setPosition(x, y);
        square.setFillColor(squares[i]->getColor()); // צבע המשבצת
        square.setOutlineColor(sf::Color::Black);
        square.setOutlineThickness(1.0f);

        // הגדרת מיקום הטקסט
        squareText.setPosition(x + 5, y + 5);

        window.draw(square);
        window.draw(squareText);
    }

    window.display();
}

void Board::auctionProperty(Square* property, std::vector<Player*>& players, sf::RenderWindow& window) {
    std::cout << "Auction started for: " << property->getName() << std::endl;

    // Cast property to PropertySquare* to ensure that we can use the setOwner method
    PropertySquare* propertySquare = dynamic_cast<PropertySquare*>(property);
    if (!propertySquare) {
        std::cerr << "Error: The property being auctioned is not a PropertySquare." << std::endl;
        return;
    }

    int highestBid = 0;
    Player* highestBidder = nullptr;
    bool auctionActive = true;
    std::vector<bool> playerDroppedOut(players.size(), false);

    while (auctionActive) {
        auctionActive = false;

        for (size_t i = 0; i < players.size(); ++i) {
            if (playerDroppedOut[i]) {
                continue;
            }

            std::cout << players[i]->getName() << ", do you want to bid? (current highest bid is $" << highestBid << ") (y/n): ";
            char choice;
            std::cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                std::cout << "Enter your bid: ";
                int bid;
                std::cin >> bid;

                if (bid > highestBid && bid <= players[i]->getBalance()) {
                    highestBid = bid;
                    highestBidder = players[i];
                    auctionActive = true;
                    std::cout << players[i]->getName() << " bids $" << bid << std::endl;
                } else {
                    std::cout << "Invalid bid (either too low or you don't have enough money)." << std::endl;
                }
            } else {
                std::cout << players[i]->getName() << " drops out of the auction." << std::endl;
                playerDroppedOut[i] = true;
            }
        }

        if (std::all_of(playerDroppedOut.begin(), playerDroppedOut.end(), [](bool droppedOut) { return droppedOut; })) {
            break;
        }
    }

    // If we have a valid highest bidder and the property is a valid PropertySquare
    if (highestBidder && propertySquare) {
        highestBidder->setBalance(highestBidder->getBalance() - highestBid);
        
        // If the player holds properties as unique_ptrs, we need to pass ownership of the property
        std::unique_ptr<PropertySquare> purchasedProperty(std::move(propertySquare));  
        highestBidder->addProperty(std::move(purchasedProperty));  // Add property to the player
        propertySquare->setOwner(highestBidder);  // Set the new owner of the property
        std::cout << highestBidder->getName() << " won the auction for " << propertySquare->getName() << " with a bid of $" << highestBid << "." << std::endl;
    } else {
        std::cout << "No one bought the property." << std::endl;
    }

    renderBoard(window);  // Re-render the board after auction
}
std::vector<Square*> Board::getPropertiesByColor(const sf::Color& color) const {
    std::vector<Square*> filteredProperties;
    for (const auto& square : squares) {
        if (auto ps = dynamic_cast<PropertySquare*>(square.get())) {
            if (ps->getColor() == color) {
                filteredProperties.push_back(ps);
            }
        }
    }
    return filteredProperties;
}

Dice& Board::getDice() {
    return dice;
}
