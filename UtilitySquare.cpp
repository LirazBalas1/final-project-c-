//Liraz Balas
//211801220
//lbalad13@gmail.com
#include "UtilitySquare.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

UtilitySquare::UtilitySquare(const std::string& name, int cost)
    : Square(name), cost(cost), owner(nullptr) {}

  sf::Color UtilitySquare::getColor() const  {
        return sf::Color::Cyan;  // ציאן או כחול בהיר
    }    

int UtilitySquare::getCost() const {
    return cost;
}

int UtilitySquare::calculateRent(int diceRoll) const {
    if (owner == nullptr) return 0;
    int multiplier = (owner->getNumberOfUtilities() == 1) ? 4 : 10;
    return diceRoll * multiplier;  // החישוב לפי מספר השירותים בבעלות הבעלים
}

void UtilitySquare::buyProperty(Player* player) {
    if (owner == nullptr && player->getBalance() >= cost) {
        player->addMoney(-cost);  // הורדת העלות מהשחקן
        setOwner(player);  // הגדרת השחקן כבעלים
        std::cout << player->getName() << " bought " << getName() << " for $" << cost << std::endl;  // הודעה על הרכישה
    } else if (owner != nullptr) {
        std::cout << getName() << " is already owned by " << owner->getName() << std::endl;  // הנכס כבר בבעלות
    } else {
        std::cout << player->getName() << " does not have enough money to buy " << getName() << std::endl;  // אין מספיק כסף
    }
}

void UtilitySquare::action(Player* player, Board* board) {
    if (owner == nullptr) {
        // הצעת רכישת השירות
        buyProperty(player);
    } else if (owner != player) {
        // תשלום שכר דירה לפי תוצאת הקוביות
        int diceRoll = board->getDice().getTotal();  // קבלת תוצאת הקוביות
        int rent = calculateRent(diceRoll);
        player->payRent(rent, owner);  // תשלום שכר דירה לבעלים
        std::cout << player->getName() << " landed on " << getName() << " and owes $" << rent << " in rent." << std::endl;  // הודעה על התשלום
    }
}

void UtilitySquare::render(sf::RenderWindow& window, sf::Vector2f position, float size, const sf::Font& font) {
    // ציור המשבצת על הלוח
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(position);
    square.setFillColor(sf::Color(200, 200, 200));  // צבע אפור בהיר
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(1.0f);
    window.draw(square);

    // הצגת שם השירות
    sf::Text nameText(name, font, 10);
    nameText.setPosition(position.x + 5, position.y + 5);
    nameText.setFillColor(sf::Color::Black);
    window.draw(nameText);

    // הצגת עלות השירות
    sf::Text costText("$" + std::to_string(cost), font, 10);
    costText.setPosition(position.x + 5, position.y + size - 20);
    costText.setFillColor(sf::Color::Black);
    window.draw(costText);

    // הצגת סימון של הבעלים אם ישנו
    if (owner) {
        sf::CircleShape ownerToken(5);
        ownerToken.setFillColor(owner->getColor());
        ownerToken.setPosition(position.x + size - 15, position.y + 5);
        window.draw(ownerToken);
    }
}

UtilitySquare::~UtilitySquare() {
    // Destructor – כרגע אין צורך בשחרור זיכרון נוסף
}
