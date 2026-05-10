#include "PowerUp.h"

PowerUp::PowerUp(PowerUpType type, sf::Vector2f position)
{
    this->type = type;
    this->isActive = true;
    this->duration = 5.0f;
    this->timer = 0.0f;

    if (type == PowerUpType::SHIELD)
        texture.loadFromFile("assets/shield_bronze.png");
    else if (type == PowerUpType::RAPID_FIRE)
        texture.loadFromFile("assets/bolt_gold.png");
    else
        texture.loadFromFile("assets/powerupGreen_star.png");

    sprite = new sf::Sprite(texture);

    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

    sprite->setPosition(position);
}

PowerUp::~PowerUp()
{
    delete sprite;
}

void PowerUp::update(float dt)
{
    timer += dt;

    if (timer >= duration)
    {
        isActive = false;
    }
}

void PowerUp::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(*sprite);
    }
}

sf::FloatRect PowerUp::getBounds()
{
    return sprite->getGlobalBounds();
}

void PowerUp::apply()
{
    if (type == PowerUpType::SHIELD)
    {
        // player take shild
        
    }
    else if (type == PowerUpType::RAPID_FIRE)
    {
     
    }
    else if (type == PowerUpType::EXTRA_LIFE)
    {
 
    }

    isActive = false;
}

bool PowerUp::getIsActive()
{
    return isActive;
}

PowerUpType PowerUp::getType()
{
    return type;
}