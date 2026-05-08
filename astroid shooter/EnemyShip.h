
#pragma once
#include "Enemy.h"

class EnemyShip : public Enemy
{
private:
    float oscillateSpeed;
    float oscillateRange;
    float oscillateOffset;
    bool driftingDown;

public:
    EnemyShip(sf::Vector2f position);

    void update(sf::Vector2f playerPosition, float dt) override;
    void draw(sf::RenderWindow& window) override;

    void oscillate(float dt);
    void driftDown(float dt);
};