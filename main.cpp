//Esteban Mora
//Carlos Vega
//Andreas Hitt
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "LinkedList.h"
#include "Player.h"
#include "RandomEvent.h"
#include "Shop.h"
#include "Combat.h"
#include "SaveSystem.h"

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
    std::vector<Room> rooms;
    Player player;
    RandomEvent events;
    Combat combat;
    SaveSystem saveSystem;

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
        getline(ss, itemName, ',');
        string enemyName, enemyHealthStr, enemyDamageStr;
        getline(ss, enemyName, ',');
        getline(ss, enemyHealthStr, ',');
        getline(ss, enemyDamageStr);
        
        stringstream as(acts);
        string action;
        vector<string> actionList;
        while (getline(as, action, ';')) {
            actionList.push_back(action);
        }

        vector<Enemy> enemies;
        if (!enemyName.empty()) {
            int eh = stoi(enemyHealthStr);
            int ed = stoi(enemyDamageStr);
            enemies.push_back(Enemy(enemyName, eh, ed));
        }

        rooms.push_back(Room(name, desc, actionList, std::vector<Item>{Item(itemName)}, enemies));
    }

    Shop shop;
    shop.addItem(Item("Sword", "Rare", 5, 50));
    shop.addItem(Item("Shield", "Uncommon", 8, 40));
    shop.addItem(Item("Potion", "Common", 1, 20));

    size_t currentIndex = 0;
    cout << "Load save? (y/n): ";
    char loadChoice;
    cin >> loadChoice;
    if (loadChoice == 'y' || loadChoice == 'Y') {
        if (saveSystem.load(player, currentIndex)) {
            cout << ">> Save loaded!" << endl;
        } else {
            cout << ">> No save found, starting new game." << endl;
            currentIndex = 0;
        }
    } else {
        currentIndex = 0;
    }
    cin.ignore(1000, '\n');

    while (currentIndex < rooms.size() && player.isAlive()) {
        displayPlayerReport(player);
        cout << rooms[currentIndex].toString();

        int count = 1;
        for (const auto& a : rooms[currentIndex].getActions()) {
            cout << count++ << ". " << a << endl;
        }
        cout << "9. Save Game" << endl;

        int choice;
        cout << "\nChoose (1-9): ";
        if (!(cin >> choice)) break;
        cin.ignore(1000, '\n');

        if (choice < 1 || choice > 9) {
            cout << "Invalid choice. Please choose a number between 1 and 9." << endl;
            continue;
        }

        string chosenAction;
        if (choice == 9) {
            chosenAction = "Save Game";
        } else if (choice >= 1 && choice < count) {
            chosenAction = rooms[currentIndex].getActions()[choice-1];
        } else {
            cout << "Invalid choice." << endl;
            continue;
        }

        if (chosenAction == "Leave the room") {
            currentIndex++;
        } else if (chosenAction == "Visit Shop") {
            visitShop(shop, player);
        } else if (chosenAction == "Save Game") {
            saveSystem.save(player, currentIndex);
            cout << ">> Game saved!" << endl;
        } else {
            // Combat first
            for (auto& enemy : rooms[currentIndex].getEnemies()) {
                if (!combat.fight(player, enemy)) {
                    cout << "\n*** GAME OVER ***\nYou died after finding " << player.getInvSize() << " items." << endl;
                    return 0;
                }
            }
            if (!checkEventSafety(player)) executeEvent(events, player);
            processLoot(player, rooms[currentIndex]);
            handleSurvivalBonus(player);
        }

        if (!player.isAlive()) {
            cout << "\n*** GAME OVER ***\nYou died after finding " << player.getInvSize() << " items." << endl;
            return 0;
        }
    }

    if (currentIndex >= rooms.size()) {
        cout << "\nCongratulations! You escaped the castle!" << endl;
    }
    return 0;
}