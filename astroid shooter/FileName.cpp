#include <SFML/Graphics.hpp>

int main()
{
    // Create a 800x600 window titled "SFML 3.0.2 Test"
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3.0.2 Test");

    // Create a circle with radius 50
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ 375.f, 275.f }); // Centers the circle

    // Game loop
    while (window.isOpen())
    {
        // Handle events (like clicking the X to close)
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();      // Clear the previous frame
        window.draw(shape);  // Draw the green circle
        window.display();    // Show everything on the screen
    }

    return 0;
}