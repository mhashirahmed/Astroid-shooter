#pragma once
#include "Enemy.h"
#include "Bullet.h"
class EnemyShip : public Enemy
{
private:
    float oscillateSpeed;
    float oscillateRange;
    float oscillateOffset;
    bool driftingDown;

public:
    Bullet* enemyBullets[20];
    int enemyBulletCount;
    float shootTimer;
    float shootInterval;  // how often they shoot
    EnemyShip(sf::Vector2f position);
    void update(sf::Vector2f playerPosition, float dt) override;
    void draw(sf::RenderWindow& window) override;
    void oscillate(float dt);
    void driftDown(float dt);
    void updateBullets(float dt);
    void drawBullets(sf::RenderWindow& window);
    void shoot(sf::Vector2f playerPosition) override;
    ~EnemyShip();

};