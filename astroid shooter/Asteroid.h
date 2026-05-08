#pragma once
#include <SFML/Graphics.hpp>
#include <string>
const int Large = 3;
const int Medium = 2;
const int Small = 1;

class Asteroid {
private:
	int size;
	sf::Texture texture;
	sf::Sprite *sprite;
	sf::Vector2f velocity;
	float rotation_speed;
public:
	Asteroid(int size, sf::Vector2f position);
	void update(float dt);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds();
	bool can_split();
	Asteroid* split();
	int getsSize();
	~Asteroid();
};