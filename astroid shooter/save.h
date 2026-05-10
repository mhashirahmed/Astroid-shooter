#pragma once

#include "Player.h"
#include <string>

using namespace std;

class SaveSystem
{
private:

    string filename;

public:

    SaveSystem();

    void saveGame(Player& player, int level);

    void loadGame(Player& player, int& level);

    bool saveExists();
};