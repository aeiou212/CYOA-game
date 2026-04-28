#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    std::string name;
    std::string rarity;
    int weight;
    int price;

    Item(std::string n = "None", std::string r = "Common", int w = 1, int p = 0) 
        : name(n), rarity(r), weight(w), price(p) {}
};

#endif