#include "SaveSystem.h"

#include <fstream>
#include <iostream>

using namespace std;

SaveSystem::SaveSystem()
{
    filename = "savegame.txt";
}

bool SaveSystem::saveExists()
{
    ifstream file(filename);

    return file.good();
}

void SaveSystem::saveGame(Player& player, int level)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Error opening save file!\n";
        return;
    }

    // save level
    file << level << endl;

    // save health and score
    file << player.health << endl;
    file << player.score << endl;

    // save position
    file << player.position.x << endl;
    file << player.position.y << endl;

    // save velocity
    file << player.velocity.x << endl;
    file << player.velocity.y << endl;

    // save rotation
    file << player.sprite.getRotation().asDegrees() << endl;

    file.close();

    cout << "Game Saved Successfully!\n";
}

void SaveSystem::loadGame(Player& player, int& level)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "No Save File Found!\n";
        return;
    }

    float rotation;

    // load level
    file >> level;

    // load health and score
    file >> player.health;
    file >> player.score;

    // load position
    file >> player.position.x;
    file >> player.position.y;

    // load velocity
    file >> player.velocity.x;
    file >> player.velocity.y;

    // load rotation
    file >> rotation;

    // apply loaded data to sprite
    player.sprite.setPosition(player.position);

    player.sprite.setRotation(degrees(rotation));

    file.close();

    cout << "Game Loaded Successfully!\n";
}