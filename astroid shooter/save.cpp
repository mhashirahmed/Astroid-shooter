#include "save.h"
#include "EnemyShip.h"
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

void SaveSystem::saveGame(Player& player, int level, EnemyShip** enemies, int enemyCount) {
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

    int aliveCount = 0;
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] && enemies[i]->getIsAlive())
            aliveCount++;
    }

    file << aliveCount << endl;

    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i] || !enemies[i]->getIsAlive()) continue;

        sf::Vector2f pos = enemies[i]->getPosition();
        file << pos.x << endl;
        file << pos.y << endl;
        file << enemies[i]->getHp() << endl;
    }

    file.close();
    cout << "Game Saved!\n";
}

void SaveSystem::loadGame(Player& player, int& level, EnemyShip** enemies, int& enemyCount) {
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
    player.setPosition(sf::Vector2f(px, py));
    player.setVelocity(sf::Vector2f(vx, vy));
    player.setSpriteDegrees(rot);

    for (int i = 0; i < enemyCount; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
    }

    file >> enemyCount;

    for (int i = 0; i < enemyCount; i++) {
        float ex, ey;
        int ehp;
        file >> ex >> ey >> ehp;

        EnemyShip* es = new EnemyShip(sf::Vector2f(ex, ey));
        es->setHp(ehp);
        enemies[i] = es;
    }

    file.close();
    cout << "Game Loaded!\n";
}