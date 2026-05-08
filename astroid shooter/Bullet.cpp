#include "Bullet.h"
#include <cmath>
Bullet::Bullet(float startX, float startY, float angle) {
	position = Vector2f(startX, startY);
	speed = 60.f;
	velocity.x = cos(angle) * speed;
	velocity.y = sin(angle) * speed; // changes depeding where its facing and stuff
	damage = 1.f;// dummy values for now will change depding on the feel of game
	active = true;
	lifetime = 0.f;
	maxlifetime = 2.f;
	texture.loadFromFile("assets/laserBlue05.png");
	sprite.setTexture(texture);
	Vector2u size = texture.getSize();
	sprite.setOrigin(Vector2f((float)size.x / 2.f, (float)size.y / 2.f));
	sprite.setPosition(position); // same scene as did for player
	sprite.setRotation(degrees(angle)); // rotate bullet to face direction
}
void Bullet::update(float dt) {
	if (!active)
		return; // it wont run if the bullet is deactivated
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	sprite.setPosition(position); // 3 lines same as movement for player
	lifetime += dt;
	if (lifetime >= maxlifetime)
		active = false; // if bullets lifespan has become longer than the max we set for it
}
void Bullet::draw(RenderWindow& window) {
	if (!active) return;
	window.draw(sprite); // again we just draw if its active
}
bool Bullet::isActive() const { 
	return active; // simple getter
}
void Bullet::deactivate() {
	active = false; // simple setter 
}
float Bullet::getDamage() const { 
	return damage; // simple setter
}
FloatRect Bullet::getBounds() const {
	return sprite.getGlobalBounds(); // form our game object class
}
