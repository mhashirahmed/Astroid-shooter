#include "save.h"
#include <fstream>
#include <iostream>
using namespace std;
SaveSystem::SaveSystem() {
    filename = "savegame.txt";
}
bool SaveSystem::saveExists() {
    ifstream file(filename);
    return file.good();
}
void SaveSystem::saveGame(Player& player, int level) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening save file!\n";
        return;
    }
    file << level << endl;
    file << player.getHealth() << endl;
    file << player.getScore() << endl;
    file << player.getPosition().x << endl;
    file << player.getPosition().y << endl;
    file << player.getVelocity().x << endl;
    file << player.getVelocity().y << endl;
    file << player.getSpriteDegrees() << endl;
    file.close();
    cout << "Game Saved!\n";
}
void SaveSystem::loadGame(Player& player, int& level) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No Save File Found!\n";
        return;
    }
    int h, s;
    float px, py, vx, vy, rot;
    file >> level;
    file >> h;
    file >> s;
    file >> px >> py;
    file >> vx >> vy;
    file >> rot;
    player.setHealth(h);
    player.setScore(s);
    player.setPosition(Vector2f(px, py));
    player.setVelocity(Vector2f(vx, vy));
    player.setSpriteDegrees(rot);
    file.close();
    cout << "Game Loaded!\n";
}