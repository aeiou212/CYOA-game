#include "Player.h"

Player::Player() : health(100), money(50), luck(5), damage(10) {}

void Player::adjustHealth(int amount) { health += amount; }
void Player::adjustMoney(int amount) { money += amount; }
void Player::addLuck(int amount) { luck += amount; }
void Player::addItem(Item item) { inventory.add(item); }

int Player::getHealth() const { return health; }
int Player::getMoney() const { return money; }
int Player::getLuck() const { return luck; }
int Player::getDamage() const { return damage; }
int Player::getInvSize() const { return inventory.getSize(); }
bool Player::isAlive() const { return health > 0; }

void Player::displayStatus() const {
    std::string condition = (health < 30) ? "WOUNDED" : "HEALTHY";
    std::cout << "\n========================================" << std::endl;
    std::cout << " STATUS: " << condition << " | HP: " << health << " | Gold: " << money << " | Luck: " << luck << std::endl;
    std::cout << " INV: ";
    if(inventory.getSize() == 0) std::cout << "Empty";
    for (const auto& item : inventory.getItems()) std::cout << "[" << item.name << "] ";
    std::cout << "\n========================================" << std::endl;
}

Inventory& Player::getInventory() { return inventory; }
bool Player::hasItem(const std::string& name) { return inventory.search(name) != nullptr; }
void Player::removeItem(const std::string& name) { inventory.remove(name); }