//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "GameController.hpp"
#include "PropertySquare.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>


GameController::GameController() : currentPlayerIndex(0), gameEnded(false), numberOfPlayers(2) {  // ברירת מחדל ל-2 שחקנים
    if (!font.loadFromFile("Roboto-Black.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
}
void GameController::initializeGame(int numPlayers, int aiPlayers, sf::RenderWindow& window) {
    players.clear();
    std::vector<sf::Color> colors = {
        sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow,
        sf::Color::Magenta, sf::Color::Cyan, sf::Color::White, sf::Color::Black
    };

    // הוספת שחקנים אמיתיים
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(std::make_unique<Player>("Player " + std::to_string(i + 1), 1500, colors[i], false));
    }

    // הוספת שחקנים ממוחשבים
    for (int i = 0; i < aiPlayers; ++i) {
        players.push_back(std::make_unique<Player>("AI Player " + std::to_string(i + 1), 1500, colors[numPlayers + i], true));
    }
    // הכנת הלוח לאחר בחירת השחקנים עם החלון
    board.renderBoard(window);
}
void GameController::startGame(sf::RenderWindow& window) {
    while (window.isOpen()) {
        handleEvents(window);

        if (!gameEnded) {
            Player* currentPlayer = players[currentPlayerIndex].get();
            playerTurn(currentPlayer, window);

            if (hasWinner()) {
                gameEnded = true;
                Player* winner = getWinner();
                logGameInfo("Game Over! " + winner->getName() + " wins!");
            } else {
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            }
        }

        renderGame(window);
    }
}
bool GameController::isAIPlayer(int playerIndex) {
    return players[playerIndex]->isAIPlayer();
}

void GameController::aiPlayerTurn(Player* player, sf::RenderWindow& window) {
    logGameInfo(player->getName() + "'s turn (AI).");

    int roll = dice.roll();
    logGameInfo(player->getName() + " (AI) rolled a " + std::to_string(roll));

    // העברת השחקן למקום החדש בלוח
    player->move(roll, board);

    // הצגת המצב הנוכחי של הלוח
    board.renderBoard(window);

    // האם השחקן נחת על משבצת שניתן לקנות?
    Square* landedSquare = board.getSquareAtPosition(player->getPosition());
    if (landedSquare) {
        logGameInfo(player->getName() + " (AI) landed on " + landedSquare->getName() + ".");

        PropertySquare* propertySquare = dynamic_cast<PropertySquare*>(landedSquare);
        if (propertySquare && propertySquare->getOwner() == nullptr) {
            // השחקן הממוחשב קונה נכס אם יש לו מספיק כסף
            if (player->getBalance() >= propertySquare->getCost()) {
                player->buyProperty(propertySquare);
                logGameInfo(player->getName() + " (AI) bought " + propertySquare->getName() + ".");
                board.renderBoard(window);
            }
        }
    }

    // השחקן הממוחשב מחליט האם לסחור או לבנות
    if (player->getBalance() > 500) {
        handleBuild(player, window);  // נניח שהוא בונה אם יש לו מעל 500$
    } else {
        logGameInfo(player->getName() + " (AI) chose not to build.");
    }

    displayMessages();

    // השהייה קצרה לפני המעבר לשחקן הבא
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void GameController::removePlayer(Player* player) {
    // חיפוש השחקן ברשימת השחקנים
    auto it = std::find_if(players.begin(), players.end(),
                           [player](const std::unique_ptr<Player>& p) {
                               return p.get() == player;
                           });

    // אם השחקן נמצא, נסיר אותו
    if (it != players.end()) {
        std::cout << player->getName() << " has been removed from the game." << std::endl;
        players.erase(it);  // הסרה מתוך הווקטור
    } else {
        std::cerr << "Error: Player not found!" << std::endl;
    }
}

void GameController::playerTurn(Player* player, sf::RenderWindow& window) {
    logGameInfo(player->getName() + "'s turn.");

    // בדיקה אם השחקן נמצא בכלא
    if (player->isInJail()) {
        std::cout << player->getName() + " is in jail." << std::endl;
        std::cout << "Do you want to (1) pay $50 to get out or (2) roll for doubles? (1/2): ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            player->addMoney(-50);  // תשלום 50 דולר כדי לצאת מהכלא
            player->getOutOfJail();
            logGameInfo(player->getName() + " paid $50 to get out of jail.");
        } else if (choice == 2) {
            int roll = dice.roll();
            logGameInfo(player->getName() + " rolled a " + std::to_string(roll));
            if (dice.isDouble()) {
                player->getOutOfJail();  // אם יצאו קוביות כפולות, השחקן משתחרר מהכלא
                logGameInfo(player->getName() + " rolled doubles and got out of jail.");
            } else {
                player->incrementJailTurn();  // עדכון מספר התורות בכלא
                logGameInfo(player->getName() + " did not roll doubles and stays in jail.");
                return;  // אם השחקן נשאר בכלא, התור שלו נגמר
            }
        }
    } else {
        // הנחת קוביות אם השחקן אינו בכלא
        int roll = dice.roll();
        logGameInfo(player->getName() + " rolled a " + std::to_string(roll));

        // העברת השחקן למקום החדש בלוח
        player->move(roll, board);
    }

    // הצגת המצב הנוכחי של הלוח
    board.renderBoard(window);

    // האם השחקן נחת על משבצת שניתן לקנות?
    Square* landedSquare = board.getSquareAtPosition(player->getPosition());
    if (landedSquare) {
        logGameInfo(player->getName() + " landed on " + landedSquare->getName() + ".");

        PropertySquare* propertySquare = dynamic_cast<PropertySquare*>(landedSquare);
        if (propertySquare && propertySquare->getOwner() == nullptr) {
            std::cout << "Do you want to buy " << propertySquare->getName() 
                      << " for $" << propertySquare->getCost() << "? (y/n): ";
            char choice;
            std::cin >> choice;

            if (choice == 'y') {
                player->buyProperty(propertySquare);
                logGameInfo(player->getName() + " bought " + propertySquare->getName() + ".");
                board.renderBoard(window);
            } else {
                logGameInfo(player->getName() + " chose not to buy " + propertySquare->getName() + ".");
            }
        } else if (propertySquare && propertySquare->getOwner() != player) {
            int rent = propertySquare->calculateRent();
            player->payRent(rent, propertySquare->getOwner());
            logGameInfo(player->getName() + " owes $" + std::to_string(rent) + " in rent.");
            board.renderBoard(window);
        }
    }

    // האם השחקן רוצה לבצע עסקה או בנייה?
    std::cout << "Do you want to trade or build? (t/b/n): ";
    char action;
    std::cin >> action;
    if (action == 't') {
        handleTrade(player, window);  // הפעלת פונקציית מסחר
    } else if (action == 'b') {
        handleBuild(player, window);  // הפעלת פונקציית בנייה
    }

    // הצגת ההודעות האחרונות
    displayMessages();

    // השהייה לפני המעבר לשחקן הבא
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void GameController::logGameInfo(const std::string& info) {
    std::cout << info << std::endl;
    gameMessages.push_back(info);
    if (gameMessages.size() > 10) {
        gameMessages.pop_front();
    }
}

void GameController::logPlayerStats() {
    for (const auto& player : players) {
        std::cout << player->getName() << " - Balance: $" << player->getBalance();
        std::cout << ", Properties: ";
        auto properties = player->getPropertySquares();
        for (const auto& property : properties) {
            std::cout << property->getName() << ", ";
        }
        std::cout << std::endl;
    }
}

void GameController::displayMessages() {
    while (!gameMessages.empty()) {
        std::cout << gameMessages.front() << std::endl;
        gameMessages.pop_front();
    }
}

void GameController::handleTrade(Player* player, sf::RenderWindow& window) {
    logGameInfo(player->getName() + " is initiating a trade.");
    auto properties = player->getPropertySquares();

    if (properties.empty()) {
        std::cout << player->getName() + " has no properties to trade." << std::endl;
        return;
    }

    std::cout << "Choose a property to trade (enter number):" << std::endl;
    for (size_t i = 0; i < properties.size(); ++i) {
        std::cout << i + 1 << ". " << properties[i]->getName() << std::endl;
    }

    int propertyIndex;
    std::cin >> propertyIndex;

    if (propertyIndex > 0 && static_cast<size_t>(propertyIndex) <= properties.size()) {
        PropertySquare* property = properties[propertyIndex - 1];

        std::cout << "Do you want to sell or mortgage " << property->getName() << "? (s/m): ";
        char choice;
        std::cin >> choice;

        if (choice == 's') {
            std::cout << "Enter the selling price: ";
            int price;
            std::cin >> price;

            if (price > 0) {
                player->addMoney(price);
                player->removeProperty(property);
                logGameInfo(player->getName() + " sold " + property->getName() + " for $" + std::to_string(price));
            } else {
                logGameInfo("Invalid price entered for selling.");
            }
        } else if (choice == 'm') {
            if (!property->isMortgaged()) {
                player->addMoney(property->getMortgageValue());
                property->setMortgaged(true);
                logGameInfo(player->getName() + " mortgaged " + property->getName() + ".");
            } else {
                logGameInfo(property->getName() + " is already mortgaged.");
            }
        } else {
            logGameInfo("Invalid choice.");
        }
    } else {
        logGameInfo("Invalid property selection.");
    }

    // Render the updated board
    board.renderBoard(window);
}

void GameController::handleBuild(Player* player, sf::RenderWindow& window) {
    auto properties = player->getPropertySquares();

    if (properties.empty()) {
        std::cout << "You don't have any properties to build on." << std::endl;
        return;
    }

    std::cout << "Choose a property to build on (enter number):" << std::endl;
    for (size_t i = 0; i < properties.size(); ++i) {
        std::cout << i + 1 << ". " << properties[i]->getName() << std::endl;
    }

    int propertyIndex;
    std::cin >> propertyIndex;

    if (propertyIndex > 0 && static_cast<size_t>(propertyIndex) <= properties.size()) {
        PropertySquare* property = properties[propertyIndex - 1];

        if (property->canBuildHouse()) {
            property->buildHouse();
            logGameInfo(player->getName() + " built a house on " + property->getName() + ".");
        } else if (property->canBuildHotel()) {
            property->buildHotel();
            logGameInfo(player->getName() + " built a hotel on " + property->getName() + ".");
        } else {
            logGameInfo("No building options available on " + property->getName() + ".");
        }
    } else {
        logGameInfo("Invalid property selection.");
    }

    // Render the updated board with the new building
    board.renderBoard(window);
}

bool GameController::hasWinner() const {
    return players.size() == 1 || std::any_of(players.begin(), players.end(),
        [](const std::unique_ptr<Player>& p) { return p->getBalance() >= 2000; });
}

Player* GameController::getWinner() const {
    if (players.size() == 1) {
        return players[0].get();
    }
    auto it = std::max_element(players.begin(), players.end(),
        [](const std::unique_ptr<Player>& a, const std::unique_ptr<Player>& b) { return a->getBalance() < b->getBalance(); });
    return it->get();
}

void GameController::renderGame(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    board.renderBoard(window);
    for (const auto& player : players) {
        player->render(window, font);
    }
    window.display();
}

void GameController::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // פעולה זו סוגרת את חלון המשחק
            window.close();
            
            // קריאה לדסטרוקטור שיבצע שחרור זיכרון
            delete this;  
        }
    }
}


GameController::~GameController() {
    // הזיכרון עבור השחקנים מנוהל אוטומטית על ידי unique_ptr ולכן אין צורך ב-delete
}
