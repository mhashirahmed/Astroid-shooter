#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "EnemyShip.h"
#include "PowerUp.h"
#include "ScoreManager.h"
#include "save.h"
using namespace sf;
enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver,
    Leaderboard
};
class GameManager {
    RenderWindow window;
    Clock clock;
    GameState state;
    int currentLevel;
    Player player;
    ScoreManager scoreManager;
    Asteroid* asteroids[50];
    EnemyShip* enemies[10];
    PowerUp* powerups[5];
    int asteroidCount;
    int enemyCount;
    int powerupCount;
    Font font;
    Text* menuTitle = nullptr;
    Text* menuStart = nullptr;
    Text* menuLeaderboard = nullptr;
    Text* menuExit = nullptr;
    Text* pauseText = nullptr;
    Text* gameOverText = nullptr;
    Text* levelText = nullptr;
    void processEvents();
    void update(float dt);
    void draw();
    void spawnAsteroids(int count);
    void spawnEnemy();
    void spawnPowerup();
    void checkCollisions();
    void checkLevelComplete();
    void startLevel(int level);
    void resetGame();
    void drawHUD();
    void drawMainMenu();
    void drawPauseMenu();
    void drawGameOver();
    void cleanupAsteroids();
    void cleanupEnemies();
    void cleanupPowerups();
    void drawEnemyArrows();
    string playerName;
    bool enteringName;
    SaveSystem saveSystem;
public:
    GameManager();
    void run();
    ~GameManager();
};