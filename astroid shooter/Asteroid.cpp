#include "Asteroid.h"
#include <cstdlib>
#include <cmath>

Asteroid::Asteroid(int size, sf::Vector2f position) {
    this->size = size;
    if (size == Large)
        texture.loadFromFile("assets/meteorBrown_big2.png");
    else if (size == Medium)
        texture.loadFromFile("assets/meteorBrown_med3.png");
    else
    {
        texture.loadFromFile("assets/meteorBrown_small2.png");
    }

    sprite = new sf::Sprite(texture);
    sf::FloatRect bounds = sprite->getLocalBounds();

    sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    sprite->setPosition(position);

    rotation_speed = (rand() % 100) / 50.f;
    float angle = (rand() % 360) * 3.14f / 180.f;

    float speed;
    if (size == Large) speed = 1.0f;
    else if (size == Medium) speed = 1.5f;
    else speed = 2.5f;
    velocity.x = cos(angle) * speed;
    velocity.y = sin(angle) * speed;
}

void Asteroid::update(float dt)
{
    sprite->move(velocity * dt * 60.f);
    sprite->rotate(sf::degrees(rotation_speed * dt * 60.f));
    sf::Vector2f pos = sprite->getPosition();
    if (pos.x < 0)   pos.x = 800;
    if (pos.x > 800) pos.x = 0;
    if (pos.y < 0)   pos.y = 600;
    if (pos.y > 600) pos.y = 0;
    sprite->setPosition(pos);
}

void Asteroid::draw(sf::RenderWindow& window)
{
    window.draw(*sprite);
}

sf::FloatRect Asteroid::getBounds()
{
    return sprite->getGlobalBounds();
}

bool Asteroid::can_split()
{
    return size != Small;
}

Asteroid* Asteroid::split()
{
    int newSize;
    if (size == Large) newSize = Medium;
    else newSize = Small;
    sf::Vector2f pos = sprite->getPosition();
    Asteroid* newAsteroids = new Asteroid[2]{
        Asteroid(newSize, pos),
        Asteroid(newSize, pos)
    };
    return newAsteroids;
}

int Asteroid::getsSize()
{
    return size;
}

Asteroid::~Asteroid() {
    delete sprite;
}