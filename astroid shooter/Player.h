#pragma once
#include "Bullet.h"
#include "GameObject.h"
class Player : public GameObject { // inherits game object
	float speed;
	float rotation;
	int health;
	int score;
	Bullet* bullets[50];
	int bulletCount;

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
	Bullet* getBullets(int i);
	int getBulletCount(); // to find how many bullets we fired we neeed these two
	int getScore(); // getters ahd setters for all of thhe members
	float getSpriteDegrees();
	void setHealth(int h);
	void setScore(int s);
	void setRotation(float degrees);
	void setSpriteDegrees(float deg);
	void reset();
	~Player(); // to get rid of bullet array we ave
};