#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "EnemyShip.h"
#include "PowerUp.h"
#include "ScoreManager.h"
using namespace sf;
enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver,
    Leaderboard
};
class GameManager {
    // core SFML
    RenderWindow window;
    Clock clock;
    // game state
    GameState state;
    int currentLevel;
    // game objects
    Player player;
    ScoreManager scoreManager;
    // dynamic arrays for objects that spawn/despawn
    Asteroid* asteroids[50];   // max 50 asteroids at once
    EnemyShip* enemies[10];    // max 10 enemies at once
    PowerUp* powerups[5];      // max 5 powerups at once
    int asteroidCount;
    int enemyCount;
    int powerupCount;
    // menu UI
    Font font;
    Text* menuTitle = nullptr; // cuz text has no default ctr we are gonna make pointers first
    Text* menuStart = nullptr;
    Text* menuLeaderboard = nullptr;
    Text* menuExit = nullptr;
    Text* pauseText = nullptr;
    Text* gameOverText = nullptr;
    Text* levelText = nullptr;
    // private methods
    void processEvents();
    void update(float dt);
    void draw(); //the draw that combines many
    void spawnAsteroids(int count);//spawns asteroids for a level
    void spawnEnemy();// spawns one enemy ship
    void spawnPowerup();//random chance to spawn powerup
    void checkCollisions();//checks all bullet/asteroid/enemy hits
    void checkLevelComplete();//moves to next level if all asteroids gone
    void startLevel(int level);//sets up a level
    void resetGame();//resets everything for new game
    void drawHUD();//draws score/health/level all 
    void drawMainMenu(); //self explainotry
    void drawPauseMenu();
    void drawGameOver();
    void cleanupAsteroids();// removes dead asteroids from array
    void cleanupEnemies();// removes dead enemies from array
    void cleanupPowerups();// removes collected powerups
public:
    GameManager();
    void run();  // starts the game loop

}; 