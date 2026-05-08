#pragma once
#include "GameObject.h"
class Bullet : public GameObject {
	float speed;
	float damage;
	bool active; // will display or hit anything or no(offscreen)
	float lifetime; // how long a bullet will be activee after shooting
	float maxlifetime; // when itll auto turn off like offscreen
public:
	Bullet(float startX, float startY, float angle);
	void update(float deltaTime) override;
	void draw(RenderWindow& window) override;
	bool isActive() const; // cehcks if active
	void deactivate();// deactivates bullet
	float getDamage() const; // tells how much damage it does
	FloatRect getBounds() const; // tells where the bullet is
};