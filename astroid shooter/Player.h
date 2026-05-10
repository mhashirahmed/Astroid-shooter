#pragma once
#include "GameObject.h"
class Player : public GameObject { // inherits game object
	float speed;
	float rotation;
	int health;
	int score;
	vector<Bullet> bullets;

public:
	Player();
	void update(float dt) override;
	void draw(RenderWindow& window) override;
	void shoot();
	void updateBullets(float dt);
	void drawBullets(RenderWindow& window);
	void takeDamage(int amount);
	int getHealth();
	Vector2f getPosition();
	vector<Bullet>& getBullets();
};