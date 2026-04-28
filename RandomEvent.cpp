#include "RandomEvent.h"

RandomEvent::RandomEvent() { srand(static_cast<unsigned int>(time(0))); }

void RandomEvent::trigger(Player& player) {
    int roll = rand() % 100;
    int luckMod = player.getLuck() / 2; 

    if (roll < 25) { // 25% chance Bad Event
        int dmg = (rand() % 15 + 10) - luckMod;
        if (dmg < 0) dmg = 0;
        std::cout << ">> [EVENT] A swarm of bats attacks! -" << dmg << " HP." << std::endl;
        player.adjustHealth(-dmg);
    } else if (roll > 75) { // 25% chance Good Event
        int find = rand() % 25 + 5;
        std::cout << ">> [EVENT] You found a loose pouch of " << find << " gold!" << std::endl;
        player.adjustMoney(find);
    } else if (roll > 45 && roll < 55) { // 10% chance Luck Gain
        std::cout << ">> [EVENT] You found a lucky charm! +2 Luck." << std::endl;
        player.addLuck(2);
    }
}