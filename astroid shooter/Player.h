#pragma once
#include "GameObject.h"
class Player : public GameObject { // inherits game object
	float speed;
	float rotation;
	int health;
	int score;
public:
	Player();
	void update(float dt) override;
	void draw(RenderWindow& window) override;
};