#include "EnemyShip.h"
#include <cmath>

EnemyShip::EnemyShip(sf::Vector2f position)
    : Enemy(position, 200, 1.5f)
{
    oscillateSpeed = 2.0f;
    oscillateRange = 100.0f;
    oscillateOffset = 0.0f;
    driftingDown = true;
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
        pos.y += 0.5f * dt * 60.f;

        if (pos.y > 600)
        {
            pos.y = 0;
        }
    }

    sprite->setPosition(pos);
}