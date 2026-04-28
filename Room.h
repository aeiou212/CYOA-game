#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"

class Room {
private:
    std::string name;
    std::string description;
    std::vector<std::string> actions;
    std::vector<Item> items;
    std::vector<Enemy> enemies;
    bool searched;

public:
    Room(std::string n, std::string d, std::vector<std::string> a, std::vector<Item> i, std::vector<Enemy> e);

    void setSearched(bool s) { searched = s; }
    bool isSearched() const { return searched; }
    std::vector<Item>& getItems() { return items; }
    const std::vector<Item>& getItems() const { return items; }
    std::vector<Enemy>& getEnemies() { return enemies; }
    const std::vector<Enemy>& getEnemies() const { return enemies; }
    void clearItems() { items.clear(); }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    std::vector<std::string> getActions() const { return actions; }
    std::string toString() const;
};

#endif