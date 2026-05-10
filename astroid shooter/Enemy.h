#pragma once
#include <SFML/Graphics.hpp>
class Enemy {
protected:
    int hp;
    float speed;
    sf::Texture texture;
    sf::Sprite* sprite;
    sf::Vector2f velocity;
    bool isAlive;

public:
    Enemy(sf::Vector2f position, int hp, float speed);
    ~Enemy();
    virtual void update(sf::Vector2f playerPosition, float dt);
    virtual void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void takeDamage(int damage);
    bool getIsAlive();
    int getHp();
    virtual void shoot(sf::Vector2f playerPosition);
};