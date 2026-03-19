#include "Room.h"

Room::Room(std::string n, std::string d, std::vector<std::string> a, Item i) 
    : name(n), description(d), actions(a), item(i), searched(false) {}

std::string Room::toString() const {
    return "Location: " + name + "\n" + description + "\n";
}