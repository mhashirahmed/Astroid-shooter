#include "EnemyShip.h"
#include <cmath>
EnemyShip::EnemyShip(sf::Vector2f position)
    : Enemy(position, 200, 1.5f)
{
    oscillateSpeed = 1.0f;
    oscillateRange = 60.0f;
    oscillateOffset = 0.0f;
    driftingDown = true;
    enemyBulletCount = 0;
    shootTimer = 0.f;
    shootInterval = 2.f;  // shoots every 2 seconds
    for (int i = 0; i < 20; i++) 
        enemyBullets[i] = nullptr;
}
void EnemyShip::update(sf::Vector2f playerPosition, float dt)
{
    oscillate(dt);

    driftDown(dt);
}

void EnemyShip::draw(sf::RenderWindow& window)
{
    Enemy::draw(window);
}

void EnemyShip::oscillate(float dt)
{
    oscillateOffset += oscillateSpeed * dt * 60.f;

    sf::Vector2f pos = sprite->getPosition();
    pos.x += sin(oscillateOffset * 3.14f / 180.f) * oscillateRange * 0.05f * dt * 60.f;

    sprite->setPosition(pos);
}

void EnemyShip::driftDown(float dt)
{
    sf::Vector2f pos = sprite->getPosition();

    if (driftingDown)
    {
        pos.y += 0.15f * dt * 60.f;

        if (pos.y > 600)
        {
            pos.y = 0;
        }
    }

    sprite->setPosition(pos);
}
void EnemyShip::shoot(sf::Vector2f playerPosition) {
    if (enemyBulletCount >= 20) return;
    sf::Vector2f enemyPos = sprite->getPosition();
    sf::Vector2f direction = playerPosition - enemyPos;
    float angle = atan2(direction.y, direction.x);
    enemyBullets[enemyBulletCount++] = new Bullet(enemyPos.x, enemyPos.y, angle,angle,true);
}

void EnemyShip::updateBullets(float dt) {
    for (int i = 0; i < enemyBulletCount; i++)
        if (enemyBullets[i]) enemyBullets[i]->update(dt);
    int newCount = 0;
    for (int i = 0; i < enemyBulletCount; i++) {
        if (enemyBullets[i] && enemyBullets[i]->isActive())
            enemyBullets[newCount++] = enemyBullets[i];
        else { delete enemyBullets[i]; enemyBullets[i] = nullptr; }
    }
    enemyBulletCount = newCount;
}

void EnemyShip::drawBullets(sf::RenderWindow& window) {
    for (int i = 0; i < enemyBulletCount; i++)
        if (enemyBullets[i]) enemyBullets[i]->draw(window);
}
EnemyShip::~EnemyShip() {
    for (int i = 0; i < 20; i++) 
        delete enemyBullets[i];
}