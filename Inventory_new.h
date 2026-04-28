#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <utility>
#include "Item.h"

class Inventory {
private:
    std::vector<Item> items;

public:
    void add(Item item);
    bool remove(const std::string& name);
    void sort();
    Item* search(const std::string& name);
    int getTotalWeight() const;
    int getSize() const;
    const std::vector<Item>& getItems() const;
};

#endif