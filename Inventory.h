#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "Item.h"

class Inventory {
private:
    std::vector<Item> items;

public:
    void add(Item item) {
        items.push_back(item);
    }

    bool remove(const std::string& name) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].name == name) {
                items.erase(items.begin() + i);
                return true;
            }
        }
        return false;
    }

    void sort() {
        // Bubble sort by name
        for (size_t i = 0; i < items.size(); ++i) {
            for (size_t j = 0; j < items.size() - 1 - i; ++j) {
                if (items[j].name > items[j + 1].name) {
                    std::swap(items[j], items[j + 1]);
                }
            }
        }
    }

    Item* search(const std::string& name) {
        // Linear search
        for (auto& item : items) {
            if (item.name == name) {
                return &item;
            }
        }
        return nullptr;
    }

    int getTotalWeight() const {
        int total = 0;
        for (const auto& item : items) {
            total += item.weight;
        }
        return total;
    }

    int getSize() const {
        return items.size();
    }

    const std::vector<Item>& getItems() const {
        return items;
    }
};

#endif</content>
<parameter name="filePath">/workspaces/CYOA-game/Inventory.h