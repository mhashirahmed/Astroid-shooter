#pragma once
#include "Screen.h"
class MainMenu : public Screen {
private:
    sf::Font font;
    sf::Text* title;
    sf::Text* playOption;
    sf::Text* leaderboardOption;
    sf::Text* exitOption;
public:
    MainMenu();
    ~MainMenu();
    void handleInput(sf::RenderWindow& window, const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};