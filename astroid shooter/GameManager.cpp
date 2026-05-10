#include "GameManager.h"
#include <cstdlib>
#include <ctime>
#include <string>
GameManager::GameManager()
    : window(VideoMode({ 800, 600 }), "Asteroid Shooter"){
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
    menuTitle = new Text(font, "ASTEROID SHOOTER", 48);
    menuStart = new Text(font, "Press ENTER to Play OR F9 to load previous save", 24);
    menuLeaderboard = new Text(font, "Press L for Leaderboard", 24);
    menuExit = new Text(font, "Press ESC to Exit", 24);
    pauseText = new Text(font, "PAUSED\nPress P to Resume\nPress M for Menu", 32);
    gameOverText = new Text(font, "GAME OVER\nPress ENTER to Play Again\nPress M for Menu", 32);
    levelText = new Text(font, "", 24);

    menuTitle->setFillColor(Color::Yellow);
    menuTitle->setPosition(Vector2f(170.f, 100.f));
    menuStart->setFillColor(Color::White);
    menuStart->setPosition(Vector2f(100.f, 250.f));
    menuLeaderboard->setFillColor(Color::White);
    menuLeaderboard->setPosition(Vector2f(260.f, 310.f));
    menuExit->setFillColor(Color::White);
    menuExit->setPosition(Vector2f(300.f, 370.f));
    pauseText->setFillColor(Color::White);
    pauseText->setPosition(Vector2f(280.f, 220.f));
    gameOverText->setFillColor(Color::Red);
    gameOverText->setPosition(Vector2f(230.f, 200.f));
    levelText->setFillColor(Color::White);
    // this we set all the text for menues

    playerName = "";
    enteringName = false;
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

        // TEXT INPUT — separate from key pressed, only when entering name
        if (state == GameState::GameOver && enteringName) {
            if (const auto* textEntered = event->getIf<Event::TextEntered>()) {
                if (textEntered->unicode == 8 && !playerName.empty()) {
                    playerName.pop_back(); // backspace
                }
                else if (textEntered->unicode >= 32 &&
                    textEntered->unicode < 128 &&
                    playerName.size() < 10) {
                    playerName += (char)textEntered->unicode;
                }
            }
        }

        // KEY PRESSED
        if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
            auto key = keyPressed->code;

            if (state == GameState::MainMenu) {
                if (key == Keyboard::Key::Enter) {
                    resetGame();
                    startLevel(1);
                    state = GameState::Playing;
                }
                if (key == Keyboard::Key::F9) {
                    if (saveSystem.saveExists()) {
                        resetGame(); // clear old state first
                        saveSystem.loadGame(player, currentLevel);
                        spawnAsteroids(3 + (currentLevel * 2)); // spawn asteroids for loaded level
                        state = GameState::Playing;
                    }
                    else {
                        cout << "No save file found!" << endl;
                    }
                }
                if (key == Keyboard::Key::L)
                    state = GameState::Leaderboard;
                if (key == Keyboard::Key::Escape)
                    window.close();
            }

            else if (state == GameState::Playing) {
                if (key == Keyboard::Key::P)
                    state = GameState::Paused;
                if (key == Keyboard::Key::Space)
                    player.shoot();
                if (key == Keyboard::Key::F5) {
                    saveSystem.saveGame(player, currentLevel); // F5 saves
                    cout << "Game Saved!" << endl;
                }
                if (key == Keyboard::Key::F9) {
                    if (saveSystem.saveExists()) {
                        saveSystem.loadGame(player, currentLevel); // F9 loads mid game
                        cout << "Game Loaded!" << endl;
                    }
                    else {
                        cout << "No save file found!" << endl;
                    }
                }
            }

            else if (state == GameState::Paused) {
                if (key == Keyboard::Key::P)
                    state = GameState::Playing;
                if (key == Keyboard::Key::M)
                    state = GameState::MainMenu;
                if (key == Keyboard::Key::F5) {
                    saveSystem.saveGame(player, currentLevel); // save from pause too
                    cout << "Game Saved!" << endl;
                }
            }

            else if (state == GameState::GameOver) {
                if (enteringName) {
                    if (key == Keyboard::Key::Enter && !playerName.empty()) {
                        scoreManager.addScore(playerName,
                            scoreManager.getCurrentScore());
                        enteringName = false;
                        playerName = "";
                    }
                }
                else {
                    if (key == Keyboard::Key::Enter) {
                        resetGame();
                        startLevel(1);
                        state = GameState::Playing;
                    }
                    if (key == Keyboard::Key::M)
                        state = GameState::MainMenu;
                }
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
    for (int i = 0; i < asteroidCount; i++)
        if (asteroids[i]) asteroids[i]->update(dt);
    sf::Vector2f playerPos = player.getPosition(); // ONLY ONCE
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i]) {
            enemies[i]->update(playerPos, dt);
            enemies[i]->shootTimer += dt;
            if (enemies[i]->shootTimer >= enemies[i]->shootInterval) {
                enemies[i]->shootTimer = 0.f;
                enemies[i]->shoot(playerPos);
            }
            enemies[i]->updateBullets(dt);
        }
    }
    for (int i = 0; i < powerupCount; i++)
        if (powerups[i]) powerups[i]->update(dt);

    checkCollisions();
    checkLevelComplete();
}
//all of our collisions
void GameManager::checkCollisions() {
    // bullets vs asteroids
    for (int b = 0; b < player.getBulletCount(); b++) {
        Bullet* bullet = player.getBullets(b);
        if (!bullet || !bullet->isActive()) continue;
        for (int i = 0; i < asteroidCount; i++) {
            if (!asteroids[i]) continue;
            if (bullet->getBounds().findIntersection(asteroids[i]->getBounds())) {
                bullet->deactivate();
                scoreManager.addPoints(100 * asteroids[i]->getsSize());
                // split asteroid if large/medium
                if (asteroids[i]->can_split() && asteroidCount + 2 <= 50) {
                    asteroids[asteroidCount++] = asteroids[i]->split();
                    asteroids[asteroidCount++] = asteroids[i]->split();
                }
                delete asteroids[i]; // deleting old asteroid
                asteroids[i] = nullptr;
            }
        }
    }

    // bullets vs enemies
    for (int b = 0; b < player.getBulletCount(); b++) {
        Bullet* bullet = player.getBullets(b);
        if (!bullet || !bullet->isActive()) continue;
        for (int i = 0; i < enemyCount; i++) {
            if (!enemies[i]) continue;
            if (bullet->getBounds().findIntersection(enemies[i]->getBounds())) {
                bullet->deactivate();
                enemies[i]->takeDamage((int)bullet->getDamage());
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
            player.takeDamage(1); // if we hit asteroid it gives us damage
            delete asteroids[i];
            asteroids[i] = nullptr;
            if (player.getHealth() <= 0) {
                state = GameState::GameOver;
                enteringName = true;
            }
        }
    }

    // player vs powerups
    for (int i = 0; i < powerupCount; i++) {
        if (!powerups[i] || !powerups[i]->getIsActive()) continue;
        if (playerBounds.findIntersection(powerups[i]->getBounds())) {
            powerups[i]->apply(); // gives powerup effect if we collide into it
            delete powerups[i];
            powerups[i] = nullptr;
        }
    }
    // enemy bullets vs player
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i]) continue;
        for (int b = 0; b < enemies[i]->enemyBulletCount; b++) {
            Bullet* bullet = enemies[i]->enemyBullets[b];
            if (!bullet || !bullet->isActive()) continue;
            if (playerBounds.findIntersection(bullet->getBounds())) {
                bullet->deactivate();
                player.takeDamage(1);
                if (player.getHealth() <= 0) {
                    state = GameState::GameOver;
                    enteringName = true;
                }
            }
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
        float x, y;
        // keep trying until spawn point is far enough from player
        do {
            x = (rand() % 2 == 0) ? 0.f : 800.f;
            y = (float)(rand() % 600);
        } while (abs(x - 400) < 150 && abs(y - 300) < 150);

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
    player.reset();
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
        for (int i = 0; i < powerupCount; i++)
            if (powerups[i]) powerups[i]->draw(window);
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i]) {
                enemies[i]->draw(window);
                enemies[i]->drawBullets(window);  // draws the enemy bullets
            }
        }
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
    Text saveHint(font, "F5 Save  F9 Load", 16);
    saveHint.setFillColor(Color(150, 150, 150));
    saveHint.setPosition(Vector2f(330.f, 575.f));
    window.draw(saveHint);
}
void GameManager::drawMainMenu() {
    window.draw(*menuTitle);
    window.draw(*menuStart);      // already updated text above
    window.draw(*menuLeaderboard);
    window.draw(*menuExit);
    // show load option only if save exists
    if (saveSystem.saveExists()) {
        Text saveExists(font, "Save file found! F9 to continue", 20);
        saveExists.setFillColor(Color::Cyan);
        saveExists.setPosition(Vector2f(230.f, 430.f));
        window.draw(saveExists);
    }
}
void GameManager::drawPauseMenu() {
    // draw game in background
    for (int i = 0; i < asteroidCount; i++)
        if (asteroids[i]) asteroids[i]->draw(window);
    player.draw(window);
    window.draw(*pauseText);
    Text saveOption(font, "Press F5 to Save Game", 24);
    saveOption.setFillColor(Color::White);
    saveOption.setPosition(Vector2f(270.f, 320.f));
    window.draw(saveOption);
}
void GameManager::drawGameOver() {
    // final score always shown
    Text finalScore(font, "Final Score: " + to_string(scoreManager.getCurrentScore()), 28);
    finalScore.setFillColor(Color::Yellow);
    finalScore.setPosition(Vector2f(280.f, 350.f));
    window.draw(finalScore);

    if (enteringName) {
        // hide game over text, show name input instead
        Text namePrompt(font, "Enter your name: " + playerName + "_", 26);
        namePrompt.setFillColor(Color::Cyan);
        namePrompt.setPosition(Vector2f(200.f, 200.f));
        window.draw(namePrompt);

        Text hint(font, "Press ENTER to confirm", 20);
        hint.setFillColor(Color::White);
        hint.setPosition(Vector2f(290.f, 260.f));
        window.draw(hint);
    }
    else {
        // only show these after name is submitted
        window.draw(*gameOverText);
        Text restart(font, "Press ENTER to Play Again    M for Menu", 22);
        restart.setFillColor(Color::White);
        restart.setPosition(Vector2f(190.f, 430.f));
        window.draw(restart);
    }
}
GameManager::~GameManager() {
    delete menuTitle;
    delete menuStart;
    delete menuLeaderboard;
    delete menuExit;
    delete pauseText;
    delete gameOverText;
    delete levelText; // destructor so no dangling pointers
}