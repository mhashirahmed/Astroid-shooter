#pragma once
#include "Screen.h"
class SettingsScreen : public Screen {
private:
    sf::Font font;
    sf::Text* title;
    sf::Text* volumeLabel;
    sf::Text* backInstruction;
    int volume;
public:
    SettingsScreen();
    ~SettingsScreen();
    void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};