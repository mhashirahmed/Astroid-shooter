
#pragma once
#include <SFML/Graphics.hpp>

enum class PowerUpType
{
    SHIELD,
    RAPID_FIRE,
    EXTRA_LIFE
};

class PowerUp
{
private:
    PowerUpType type;
    sf::Texture texture;
    sf::Sprite* sprite;
    bool isActive;
    float duration;
    float timer;

public:
    PowerUp(PowerUpType type, sf::Vector2f position);
    ~PowerUp();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void apply();
    bool getIsActive();
    PowerUpType getType();
};