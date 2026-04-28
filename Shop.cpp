#include "Shop.h"

void Shop::addItem(Item item) {
    items.push_back(item);
}

void Shop::displayItems() const {
    std::cout << "\n=== SHOP INVENTORY ===" << std::endl;
    if (items.empty()) {
        std::cout << "No items for sale." << std::endl;
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        const auto& item = items[i];
        std::cout << i + 1 << ". " << item.name << " (" << item.rarity << ") - Weight: " << item.weight << " - Price: " << item.price << " gold" << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

bool Shop::buyItem(const std::string& name, Player& player) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == name) {
            if (player.getMoney() >= it->price) {
                player.adjustMoney(-it->price);
                player.addItem(*it);
                std::cout << ">> You bought " << it->name << " for " << it->price << " gold!" << std::endl;
                items.erase(it);
                return true;
            } else {
                std::cout << ">> Not enough gold!" << std::endl;
                return false;
            }
        }
    }
    std::cout << ">> Item not found in shop." << std::endl;
    return false;
}

bool Shop::sellItem(const std::string& name, Player& player) {
    // For simplicity, sell at half price. In a real game, might check if item was bought here.
    // But since inventory doesn't track buy price, we'll assume a sell price based on rarity.
    int sellPrice = 0;
    if (name == "Sword") sellPrice = 25;
    else if (name == "Shield") sellPrice = 20;
    else if (name == "Potion") sellPrice = 10;
    else sellPrice = 5; // default

    // Check if player has the item
    if (player.hasItem(name)) {
        player.adjustMoney(sellPrice);
        player.removeItem(name);
        std::cout << ">> You sold " << name << " for " << sellPrice << " gold!" << std::endl;
        return true;
    } else {
        std::cout << ">> You don't have that item." << std::endl;
        return false;
    }
}