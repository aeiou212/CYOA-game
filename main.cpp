//Esteban Mora
//Carlos Vega
//Andreas Hitt
#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "Player.h"
#include "RandomEvent.h"
#include "Shop.h"

using namespace std;

// Function 1 & 2 (Player Focus)
void displayPlayerReport(const Player& p) {
    p.displayStatus();
}
void handleSurvivalBonus(Player& p) {
    static int actions = 0;
    if (++actions % 3 == 0) {
        cout << ">> SURVIVOR BONUS: +1 Luck!" << endl;
        p.addLuck(1);
    }
}

// Function 3 & 4 (Item Focus)
void processLoot(Player& p, Room& r) {
    if (!r.isSearched() && !r.getItems().empty()) {
        for (const auto& item : r.getItems()) {
            cout << ">> You scavenged a [" << item.name << "]!" << endl;
            p.addItem(item);
        }
        r.clearItems();
        r.setSearched(true);
    } else {
        cout << ">> This area has been thoroughly picked over." << endl;
    }
}
string getItemFlavorText(const Item& i) {
    return "The " + i.name + " feels cold in your hands.";
}

// Function 5 & 6 (Event Focus)
void executeEvent(RandomEvent& re, Player& p) {
    re.trigger(p);
}
bool checkEventSafety(const Player& p) {
    if (p.getLuck() > 20) {
        cout << ">> Your intuition warns you of danger. You avoid a trap!" << endl;
        return true;
    }
    return false;
}

// Shop Function
void visitShop(Shop& shop, Player& player) {
    cout << "\n>> You enter the castle shop!" << endl;
    while (true) {
        shop.displayItems();
        cout << "\nOptions: buy <item_name>, sell <item_name>, leave" << endl;
        cout << "Your gold: " << player.getMoney() << endl;
        cout << "> ";
        string command;
        getline(cin, command);
        if (command == "leave") break;
        size_t space = command.find(' ');
        if (space == string::npos) {
            cout << "Invalid command." << endl;
            continue;
        }
        string action = command.substr(0, space);
        string itemName = command.substr(space + 1);
        if (action == "buy") {
            shop.buyItem(itemName, player);
        } else if (action == "sell") {
            shop.sellItem(itemName, player);
        } else {
            cout << "Invalid action." << endl;
        }
    }
    cout << ">> You leave the shop." << endl;
}

int main() {
    LinkedList castle;
    Player player;
    RandomEvent events;

    ifstream file("rooms.csv");
    string line;
    if (!file.is_open()) {
        cout << "Error: Place rooms.csv in the same folder as the exe." << endl;
        return 1;
    }

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name, desc, acts, itemName;
        
        getline(ss, name, ',');
        getline(ss, desc, ',');
        getline(ss, acts, ',');
        getline(ss, itemName);
        
        stringstream as(acts);
        string action;
        vector<string> actionList;
        while (getline(as, action, ';')) {
            actionList.push_back(action);
        }

        castle.addRoom(Room(name, desc, actionList, std::vector<Item>{Item(itemName)}, std::vector<Enemy>{}));
    }

    Shop shop;
    shop.addItem(Item("Sword", "Rare", 5, 50));
    shop.addItem(Item("Shield", "Uncommon", 8, 40));
    shop.addItem(Item("Potion", "Common", 1, 20));

    auto curr = castle.getHead();
    while (curr && player.isAlive()) {
        displayPlayerReport(player);
        cout << curr->room.toString();

        int count = 1;
        for (const auto& a : curr->room.getActions()) {
            cout << count++ << ". " << a << endl;
        }

        int choice;
        cout << "\nChoose (1-" << curr->room.getActions().size() << "): ";
        if (!(cin >> choice)) break;
        cin.ignore(1000, '\n');

        if (choice < 1 || choice > (int)curr->room.getActions().size()) {
            cout << "Invalid choice. Please choose a number between 1 and " << curr->room.getActions().size() << "." << endl;
            continue;
        }

        string chosenAction = curr->room.getActions()[choice-1];

        if (chosenAction == "Leave the room") {
            curr = curr->next;
        } else if (chosenAction == "Visit Shop") {
            visitShop(shop, player);
        } else {
            if (!checkEventSafety(player)) executeEvent(events, player);
            processLoot(player, curr->room);
            handleSurvivalBonus(player);
        }

        if (!player.isAlive()) {
            cout << "\n*** GAME OVER ***\nYou died after finding " << player.getInvSize() << " items." << endl;
            return 0;
        }
    }

    cout << "\nCongratulations! You escaped the castle!" << endl;
    return 0;
}