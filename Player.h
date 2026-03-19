#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <iostream>
#include "Item.h"

class Player {
private:
    int health;
    int money;
    int luck;
    std::vector<Item> inventory;

public:
    Player() : health(100), money(50), luck(5) {}

    void adjustHealth(int amount) { health += amount; }
    void adjustMoney(int amount) { money += amount; }
    void addLuck(int amount) { luck += amount; }
    void addItem(Item item) { inventory.push_back(item); }

    int getHealth() const { return health; }
    int getLuck() const { return luck; }
    int getInvSize() const { return (int)inventory.size(); }
    bool isAlive() const { return health > 0; }
    
    void displayStatus() const {
        std::string condition = (health < 30) ? "WOUNDED" : "HEALTHY";
        std::cout << "\n========================================" << std::endl;
        std::cout << " STATUS: " << condition << " | HP: " << health << " | Gold: " << money << " | Luck: " << luck << std::endl;
        std::cout << " INV: ";
        if(inventory.empty()) std::cout << "Empty";
        for (const auto& item : inventory) std::cout << "[" << item.name << "] ";
        std::cout << "\n========================================" << std::endl;
    }
};

#endif