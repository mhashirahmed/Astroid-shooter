#pragma once
#include <SFML/Graphics.hpp>
class Screen {
public:
    virtual void handleInput(sf::RenderWindow& window, const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Screen() {}
};