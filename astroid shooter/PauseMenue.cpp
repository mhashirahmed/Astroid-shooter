#include "PauseMenu.h"
PauseMenu::PauseMenu() {
    font.openFromFile("assets/font.ttf");
    pauseTitle = new sf::Text(font, "GAME PAUSED", 60);
    resumeOption = new sf::Text(font, "Press P to Resume", 30);
    quitOption = new sf::Text(font, "Press M for Main Menu", 30);
    pauseTitle->setFillColor(sf::Color::Yellow);
    pauseTitle->setPosition(sf::Vector2f(200.f, 150.f));
    resumeOption->setFillColor(sf::Color::White);
    resumeOption->setPosition(sf::Vector2f(280.f, 300.f));
    quitOption->setFillColor(sf::Color::White);
    quitOption->setPosition(sf::Vector2f(250.f, 360.f));
}
PauseMenu::~PauseMenu() {
    delete pauseTitle;
    delete resumeOption;
    delete quitOption;
}
void PauseMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    // handled by GameManager
}
void PauseMenu::update(float dt) {}
void PauseMenu::render(sf::RenderWindow& window) {
    window.draw(*pauseTitle);
    window.draw(*resumeOption);
    window.draw(*quitOption);
}