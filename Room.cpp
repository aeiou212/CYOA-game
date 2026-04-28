#include "Room.h"

Room::Room(std::string n, std::string d, std::vector<std::string> a, std::vector<Item> i, std::vector<Enemy> e) 
    : name(n), description(d), actions(a), items(i), enemies(e), searched(false) {}

std::string Room::toString() const {
    return "Location: " + name + "\n" + description + "\n";
}