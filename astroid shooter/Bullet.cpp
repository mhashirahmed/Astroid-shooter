#include "Bullet.h"
#include <cmath>
Bullet::Bullet(float startX, float startY, float moveAngle, float visualAngle, bool isEnemy) {
	position = Vector2f(startX, startY);
	speed = 600.f;
	velocity.x = cos(moveAngle) * speed;  // direction uses offset angle
	velocity.y = sin(moveAngle) * speed;
	damage = 1.f;
	active = true;
	lifetime = 0.f;
	maxlifetime = 2.f;
	if (isEnemy)
		texture.loadFromFile("assets/laserRed05.png");
	else
		texture.loadFromFile("assets/laserBlue05.png");
	sprite = new Sprite(texture);
	Vector2u size = texture.getSize();
	sprite->setOrigin(Vector2f(size.x / 2.f, size.y / 2.f));
	sprite->setPosition(position);
	sprite->setRotation(sf::degrees(visualAngle));
}
void Bullet::update(float dt) {
	if (!active)
		return; // it wont run if the bullet is deactivated
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	sprite->setPosition(position); // 3 lines same as movement for player
	lifetime += dt;
	if (lifetime >= maxlifetime)
		active = false; // if bullets lifespan has become longer than the max we set for it
}
void Bullet::draw(RenderWindow& window) {
	if (!active) return;
	window.draw(*sprite); // again we just draw if its active
}
bool Bullet::isActive() const { 
	return active; 
}
void Bullet::deactivate() {
	active = false; 
}
float Bullet::getDamage() const { 
	return damage; 
}
FloatRect Bullet::getBounds() const {
	return sprite->getGlobalBounds(); // form our game object class
}
