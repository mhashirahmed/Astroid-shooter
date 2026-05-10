#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class GameObject {
protected: // lets child class access
	Vector2f position; // sfml datatype with flaot x and y together
	Vector2f velocity; // x and y velocities
	Texture texture; // texture of te sprite
	Sprite* sprite = nullptr; // actual sprite/image
public:
	GameObject(); // defualt Ctr does nothing
	virtual void update(float dt) = 0;
	virtual void draw(RenderWindow& window) = 0; // not actually s etting value as 0 but ittl be redef later
	FloatRect getBounds() const;
	Vector2f getVelocity() const; // gtetter and setter
	void setVelocity(Vector2f vel);
	void setPosition(Vector2f pos);
	virtual ~GameObject();
};