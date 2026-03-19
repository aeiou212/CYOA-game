#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Item.h"

class Room {
private:
    std::string name;
    std::string description;
    std::vector<std::string> actions;
    Item item;
    bool searched;

public:
    Room(std::string n, std::string d, std::vector<std::string> a, Item i);

    void setSearched(bool s) { searched = s; }
    bool isSearched() const { return searched; }
    Item getItem() const { return item; }
    void clearItem() { item = Item("None"); }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    std::vector<std::string> getActions() const { return actions; }
    std::string toString() const;
};

#endif