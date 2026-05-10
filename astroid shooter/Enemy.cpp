#include "Enemy.h"
#include <cmath>

Enemy::Enemy(sf::Vector2f position, int hp, float speed)
{
    this->hp = hp;
    this->speed = speed;
    this->isAlive = true;

    texture.loadFromFile("assets/enemyship.png");

    sprite = new sf::Sprite(texture);

    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

    sprite->setPosition(position);
}

Enemy::~Enemy()
{
    delete sprite;
}

void Enemy::update(sf::Vector2f playerPosition, float dt)
{
    sf::Vector2f enemyPos = sprite->getPosition();
    sf::Vector2f direction = playerPosition - enemyPos;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
    {
        direction.x = direction.x / length;
        direction.y = direction.y / length;
    }

    velocity = direction * speed;

    sprite->move(velocity * dt * 60.f);
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(*sprite);
}

sf::FloatRect Enemy::getBounds()
{
    return sprite->getGlobalBounds();
}

void Enemy::takeDamage(int damage)
{
    hp -= damage;

    if (hp <= 0)
    {
        isAlive = false;
    }
}

bool Enemy::getIsAlive()
{
    return isAlive;
}

int Enemy::getHp()
{
    return hp;
}

void Enemy::setHp(int h)
{
    hp = h;
    if (hp > 0)
        isAlive = true;
}


sf::Vector2f Enemy::getPosition()
{
    return sprite->getPosition();
}

void Enemy::shoot(sf::Vector2f playerPosition)
{

}
