#include "GameManager.h"
#include <cstdlib>
#include <ctime>
#include <string>
GameManager::GameManager()
    : window(VideoMode({ 800, 600 }), "Asteroid Shooter") {
    srand(time(0));  // time random for asteroid spawning
    state = GameState::MainMenu;
    currentLevel = 1;
    asteroidCount = 0;
    enemyCount = 0;
    powerupCount = 0; // seting all to zero intially

    // initilaise with zero
    for (int i = 0; i < 50; i++) 
        asteroids[i] = nullptr;
    for (int i = 0; i < 10; i++) 
        enemies[i] = nullptr;
    for (int i = 0; i < 5; i++) 
        powerups[i] = nullptr;
    font.openFromFile("assets/font.ttf"); // loads the font

    // setup menu text
    menuTitle.setFont(font);
    menuTitle.setString("ASTEROID SHOOTER");
    menuTitle.setCharacterSize(48);
    menuTitle.setFillColor(Color::Yellow);
    menuTitle.setPosition(Vector2f(170.f, 100.f));

    menuStart.setFont(font);
    menuStart.setString("Press ENTER to Play");
    menuStart.setCharacterSize(28);
    menuStart.setFillColor(Color::White);
    menuStart.setPosition(Vector2f(270.f, 250.f));

    menuLeaderboard.setFont(font);
    menuLeaderboard.setString("Press L for Leaderboard");
    menuLeaderboard.setCharacterSize(24);
    menuLeaderboard.setFillColor(Color::White);
    menuLeaderboard.setPosition(Vector2f(260.f, 310.f));

    menuExit.setFont(font);
    menuExit.setString("Press ESC to Exit");
    menuExit.setCharacterSize(24);
    menuExit.setFillColor(Color::White);
    menuExit.setPosition(Vector2f(300.f, 370.f));

    pauseText.setFont(font);
    pauseText.setString("PAUSED\nPress P to Resume\nPress M for Menu");
    pauseText.setCharacterSize(32);
    pauseText.setFillColor(Color::White);
    pauseText.setPosition(Vector2f(280.f, 220.f));

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress ENTER to Play Again\nPress M for Menu");
    gameOverText.setCharacterSize(32);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(Vector2f(230.f, 200.f));

    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(Color::White);
    // this we set all the text for menues
}

//game loop
void GameManager::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        // cap dt so game doesnt go crazy if window is dragged
        if (dt > 0.1f) 
            dt = 0.1f;
        processEvents();
        update(dt);
        draw();
    }
    // cleanup all dynamic memory before exit
    for (int i = 0; i < 50; i++)
        if (asteroids[i]) 
            delete asteroids[i];
    for (int i = 0; i < 10; i++)
        if (enemies[i])
            delete enemies[i];
    for (int i = 0; i < 5; i++)
        if (powerups[i])  
            delete powerups[i];
}
void GameManager::processEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<Event::Closed>())
            window.close();
        if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
            auto key = keyPressed->code;
            if (state == GameState::MainMenu) {
                if (key == Keyboard::Key::Enter) {
                    resetGame();
                    startLevel(1);
                    state = GameState::Playing;
                }
                if (key == Keyboard::Key::L)
                    state = GameState::Leaderboard;
                if (key == Keyboard::Key::Escape)
                    window.close();
            }
            else if (state == GameState::Playing) {
                if (key == Keyboard::Key::P)
                    state = GameState::Paused;
                // shoot on space
                if (key == Keyboard::Key::Space)
                    player.shoot();
            }
            else if (state == GameState::Paused) {
                if (key == Keyboard::Key::P)
                    state = GameState::Playing;
                if (key == Keyboard::Key::M)
                    state = GameState::MainMenu;
            }
            else if (state == GameState::GameOver) {
                if (key == Keyboard::Key::Enter) {
                    resetGame();
                    startLevel(1);
                    state = GameState::Playing;
                }
                if (key == Keyboard::Key::M)
                    state = GameState::MainMenu;
            }

            else if (state == GameState::Leaderboard) {
                if (key == Keyboard::Key::Escape ||
                    key == Keyboard::Key::M)
                    state = GameState::MainMenu;
            }
        }
    }
}

// ── UPDATE ──
void GameManager::update(float dt) {
    if (state != GameState::Playing) return;
    player.update(dt);
    player.updateBullets(dt);
    // update asteroids
    for (int i = 0; i < asteroidCount; i++)
        if (asteroids[i])
            asteroids[i]->update(dt);
    // update enemies — pass player position for tracking
    sf::Vector2f playerPos = player.getPosition();
    for (int i = 0; i < enemyCount; i++)
        if (enemies[i]) 
            enemies[i]->update(playerPos, dt);
    // update powerups
    for (int i = 0; i < powerupCount; i++)
        if (powerups[i])
            powerups[i]->update(dt);

    checkCollisions();
    checkLevelComplete();
}
//all of our collisions
void GameManager::checkCollisions() {
    // bullets vs asteroids
    auto& bullets = player.getBullets(); // auto means get the data type automatically like in template
    for (auto& bullet : bullets) {
        if (!bullet.isActive()) 
            continue;
        for (int i = 0; i < asteroidCount; i++) {
            if (!asteroids[i])
                continue;
            if (bullet.getBounds().findIntersection(asteroids[i]->getBounds())) {
                bullet.deactivate();
                scoreManager.addPoints(100 * asteroids[i]->getsSize());
                // split asteroid if large/medium
                if (asteroids[i]->can_split() && asteroidCount + 2 <= 50) {
                    Asteroid* newOnes = asteroids[i]->split();
                    asteroids[asteroidCount++] = &newOnes[0]; // adding new astroid to the array
                    asteroids[asteroidCount++] = &newOnes[1];
                }
                delete asteroids[i]; // deleting old astorid
                asteroids[i] = nullptr;
            }
        }
    }
    // bullets vs enemies
    for (auto& bullet : bullets) {
        if (!bullet.isActive()) 
            continue;
        for (int i = 0; i < enemyCount; i++) {
            if (!enemies[i]) 
                continue;
            if (bullet.getBounds().findIntersection(enemies[i]->getBounds())) {
                bullet.deactivate();
                enemies[i]->takeDamage((int)bullet.getDamage());
                scoreManager.addPoints(500);
                if (!enemies[i]->getIsAlive()) {
                    delete enemies[i]; // deletes enemy if their life goes to zero
                    enemies[i] = nullptr;
                }
            }
        }
    }
    // player vs asteroids
    FloatRect playerBounds = player.getBounds();
    for (int i = 0; i < asteroidCount; i++) {
        if (!asteroids[i]) continue;
        if (playerBounds.findIntersection(asteroids[i]->getBounds())) {
            player.takeDamage(1); // if we hit astroid it gives us damage
            delete asteroids[i];
            asteroids[i] = nullptr;
            if (player.getHealth() <= 0)
                state = GameState::GameOver;
        }
    }
    // player vs powerups
    for (int i = 0; i < powerupCount; i++) {
        if (!powerups[i] || !powerups[i]->getIsActive()) 
            continue;
        if (playerBounds.findIntersection(powerups[i]->getBounds())) {
            powerups[i]->apply(); // gives powerup effect if we collide into it
            delete powerups[i];
            powerups[i] = nullptr;
        }
    }
    cleanupAsteroids();
    cleanupEnemies();
    cleanupPowerups();
}

void GameManager::checkLevelComplete() {
    // count remaining asteroids
    int remaining = 0;
    for (int i = 0; i < asteroidCount; i++)
        if (asteroids[i])
            remaining++;
    if (remaining == 0 && enemyCount == 0) {
        currentLevel++;
        startLevel(currentLevel);
    }
}

void GameManager::startLevel(int level) {
    currentLevel = level;
    // more asteroids each level, capped at 15
    int count = 3 + (level * 2);
    if (count > 15) count = 15;
    spawnAsteroids(count);
    // enemies start spawning from level 2
    if (level >= 2) 
        spawnEnemy();
    if (level >= 4) 
        spawnEnemy();  // two enemies from level 4
}
void GameManager::spawnAsteroids(int count) {
    for (int i = 0; i < count && asteroidCount < 50; i++) {
        // spawn on edges so they dont appear on top of player
        float x = (rand() % 2 == 0) ? 0.f : 800.f;
        float y = (float)(rand() % 600);
        asteroids[asteroidCount++] = new Asteroid(Large, Vector2f(x, y));
    }
}
void GameManager::spawnEnemy() {
    if (enemyCount >= 10) return;
    float x = (float)(rand() % 700 + 50);
    enemies[enemyCount++] = new EnemyShip(Vector2f(x, 0.f));
}
void GameManager::spawnPowerup() {
    if (powerupCount >= 5) return;
    float x = (float)(rand() % 700 + 50);
    float y = (float)(rand() % 500 + 50);
    // random powerup type
    int r = rand() % 3;
    PowerUpType type = (r == 0) ? PowerUpType::SHIELD :
        (r == 1) ? PowerUpType::RAPID_FIRE :
        PowerUpType::EXTRA_LIFE;
    powerups[powerupCount++] = new PowerUp(type, Vector2f(x, y));
}

void GameManager::resetGame() {
    // delete all existing objects
    for (int i = 0; i < 50; i++) { delete asteroids[i]; asteroids[i] = nullptr; }
    for (int i = 0; i < 10; i++) { delete enemies[i];   enemies[i] = nullptr; }
    for (int i = 0; i < 5; i++) { delete powerups[i];  powerups[i] = nullptr; }
    asteroidCount = 0;
    enemyCount = 0;
    powerupCount = 0;
    currentLevel = 1;
    scoreManager.resetScore();
    // reset player to center
    player = Player();
}

// ── CLEANUP ──
void GameManager::cleanupAsteroids() {
    int newCount = 0;
    for (int i = 0; i < asteroidCount; i++) {
        if (asteroids[i]) asteroids[newCount++] = asteroids[i];
    }
    for (int i = newCount; i < asteroidCount; i++) asteroids[i] = nullptr;
    asteroidCount = newCount;
}

void GameManager::cleanupEnemies() {
    int newCount = 0;
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i])
            enemies[newCount++] = enemies[i];
    }
    for (int i = newCount; i < enemyCount; i++)
        enemies[i] = nullptr;
    enemyCount = newCount;
}

void GameManager::cleanupPowerups() {
    int newCount = 0;
    for (int i = 0; i < powerupCount; i++) {
        if (powerups[i] && powerups[i]->getIsActive())
            powerups[newCount++] = powerups[i];
        else { delete powerups[i]; powerups[i] = nullptr; }
    }
    powerupCount = newCount;
}

// our draw function that calls all draw functions
void GameManager::draw() {
    window.clear(Color::Black);
    if (state == GameState::MainMenu)      
        drawMainMenu();
    else if (state == GameState::Leaderboard)
        scoreManager.draw(window);
    else if (state == GameState::Paused)   
        drawPauseMenu();
    else if (state == GameState::GameOver)  
        drawGameOver();
    else if (state == GameState::Playing) {
        // draw all game objects
        for (int i = 0; i < asteroidCount; i++)
            if (asteroids[i]) asteroids[i]->draw(window);
        for (int i = 0; i < enemyCount; i++)
            if (enemies[i]) enemies[i]->draw(window);
        for (int i = 0; i < powerupCount; i++)
            if (powerups[i]) powerups[i]->draw(window);
        player.draw(window);
        player.drawBullets(window);
        drawHUD();
    }
    window.display();
}

void GameManager::drawHUD() {
    // displaying our score
    Text scoreText(font, "Score: " + to_string(scoreManager.getCurrentScore()), 24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(Vector2f(10.f, 10.f));
    window.draw(scoreText);
    // displaying our health
    Text healthText(font, "Health: " + to_string(player.getHealth()), 24);
    healthText.setFillColor(Color::Green);
    healthText.setPosition(Vector2f(10.f, 40.f));
    window.draw(healthText);
    // displaying the level we are on level
    Text lvlText(font, "Level: " + to_string(currentLevel), 24);
    lvlText.setFillColor(Color::Yellow);
    lvlText.setPosition(Vector2f(680.f, 10.f));
    window.draw(lvlText);
}
void GameManager::drawMainMenu() {
    window.draw(menuTitle);
    window.draw(menuStart);
    window.draw(menuLeaderboard);
    window.draw(menuExit);
}
void GameManager::drawPauseMenu() {
    // draw game in background
    for (int i = 0; i < asteroidCount; i++)
        if (asteroids[i]) asteroids[i]->draw(window);
    player.draw(window);
    window.draw(pauseText);
}
void GameManager::drawGameOver() {
    Text finalScore(font, "Final Score: " + to_string(scoreManager.getCurrentScore()), 28);
    finalScore.setFillColor(Color::Yellow);
    finalScore.setPosition(Vector2f(280.f, 420.f));
    window.draw(gameOverText);
    window.draw(finalScore);
}