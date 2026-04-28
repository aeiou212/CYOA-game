#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include "Player.h"
#include <string>

class SaveSystem {
public:
    void save(const Player& player, size_t currentRoomIndex);
    bool load(Player& player, size_t& currentRoomIndex);
private:
    std::string filename = "save.txt";
};

#endif