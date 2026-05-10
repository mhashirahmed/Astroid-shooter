#include "MainMenu.h"
MainMenu::MainMenu() {
    font.openFromFile("assets/font.ttf");

    title = new sf::Text(font, "ASTEROID SHOOTER", 50);
    playOption = new sf::Text(font, "Press ENTER to Play", 30);
    leaderboardOption = new sf::Text(font, "Press L for Leaderboard", 26);
    exitOption = new sf::Text(font, "Press ESC to Exit", 26);

    title->setFillColor(sf::Color::Yellow);
    title->setPosition(sf::Vector2f(170.f, 100.f));

    playOption->setFillColor(sf::Color::White);
    playOption->setPosition(sf::Vector2f(270.f, 250.f));

    leaderboardOption->setFillColor(sf::Color::White);
    leaderboardOption->setPosition(sf::Vector2f(250.f, 310.f));

    exitOption->setFillColor(sf::Color::White);
    exitOption->setPosition(sf::Vector2f(300.f, 370.f));
}
MainMenu::~MainMenu() {
    delete title;
    delete playOption;
    delete leaderboardOption;
    delete exitOption;
}
void MainMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape)
            window.close();
    }
}
void MainMenu::update(float dt) {}
void MainMenu::render(sf::RenderWindow& window) {
    window.draw(*title);
    window.draw(*playOption);
    window.draw(*leaderboardOption);
    window.draw(*exitOption);
}