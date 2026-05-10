#pragma once

#include "Player.h"
#include "EnemyShip.h"
#include <string>

using namespace std;

class SaveSystem {
private:
    string filename;
public:
    SaveSystem();
    void saveGame(Player& player, int level, EnemyShip** enemies, int enemyCount);
    void loadGame(Player& player, int& level, EnemyShip** enemies, int& enemyCount);
    bool saveExists();
};
