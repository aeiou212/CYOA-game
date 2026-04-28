#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <iostream>
#include "Item.h"
#include "Inventory.h"

class Player {
private:
    int health;
    int money;
    int luck;
    Inventory inventory;

public:
    Player();

    void adjustHealth(int amount);
    void adjustMoney(int amount);
    void addLuck(int amount);
    void addItem(Item item);

    int getHealth() const;
    int getMoney() const;
    int getLuck() const;
    int getInvSize() const;
    bool isAlive() const;
    
    void displayStatus() const;

    Inventory& getInventory();
    bool hasItem(const std::string& name);
    void removeItem(const std::string& name);
};

#endif