#include "SettingScreen.h"

SettingsScreen::SettingsScreen() {
    font.openFromFile("assets/font.ttf");
    volume = 100;
    title = new sf::Text(font, "SETTINGS", 50);
    volumeLabel = new sf::Text(font, "Volume: 100%", 30);
    backInstruction = new sf::Text(font, "UP/DOWN to adjust volume    B to go back", 22);
    title->setFillColor(sf::Color::Yellow);
    title->setPosition(sf::Vector2f(300.f, 80.f));
    volumeLabel->setFillColor(sf::Color::White);
    volumeLabel->setPosition(sf::Vector2f(320.f, 250.f));
    backInstruction->setFillColor(sf::Color::White);
    backInstruction->setPosition(sf::Vector2f(130.f, 500.f));
}
SettingsScreen::~SettingsScreen() {
    delete title;
    delete volumeLabel;
    delete backInstruction;
}
void SettingsScreen::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) {
            if (volume < 100) {
                volume += 10;
                volumeLabel->setString("Volume: " + std::to_string(volume) + "%");
            }
        }
        if (keyPressed->code == sf::Keyboard::Key::Down) {
            if (volume > 0) {
                volume -= 10;
                volumeLabel->setString("Volume: " + std::to_string(volume) + "%");
            }
        }
    }
}
void SettingsScreen::update(float dt) {}
void SettingsScreen::render(sf::RenderWindow& window) {
    window.draw(*title);
    window.draw(*volumeLabel);
    window.draw(*backInstruction);
}