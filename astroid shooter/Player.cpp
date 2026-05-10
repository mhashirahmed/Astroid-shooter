#include "Player.h"
#include <cmath> // Needed later for sin() and cos()

// constructor for player
Player::Player() {
    texture.loadFromFile("assets/playership.png"); // loead tecxutre
    sprite = new Sprite(texture); // it wont dispolay unless we build a brand new spire for somereason
    Vector2u size = texture.getSize(); // gives sie of sprite
    sprite->setOrigin(Vector2f((float)size.x / 2.f, (float)size.y / 2.f));// setting the center of rotation so that it rotates from the center of the sprite
    position = Vector2f(400.f, 300.f); // center of a 800x600 resolution
    sprite->setPosition(position); // set the position as the center

    speed = 5000.f;
    rotation = 200.f;
    health = 3;
    score = 0;
    // intialized value(dummy forr now change later depending on feel)
    bulletCount = 0;
    for (int i = 0; i < 50; i++) bullets[i] = nullptr;
}

// the actual physics part
void Player::update(float dt) {
    //an 'if' statement checking the Left or A key.
    //    If pressed, rotate the sprite negatively using dt.
    if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left)) {
        sprite->rotate(degrees(-rotation * dt)); // in sfml 3 roatin must be in degrees
        // dt is delta time or change in time since last frame so we use in games so its same for all systems as were using seconds not frames
    }
    // checks if a or left arrow key pressed)

    if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right)) {
        sprite->rotate(degrees(rotation * dt));
    }// same code but for right rotation

    if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up)) {
        float angle = sprite->getRotation().asRadians() - 1.5708f; // -90 degrees in radians cuz its  a thhing in sfml , if we dont we cant move from and back as angle is measure from right
        velocity.x += cos(angle) * speed * dt;
        velocity.y += sin(angle) * speed * dt;
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down)) {
        float angle = sprite->getRotation().asRadians() - 1.5708f;
        velocity.x -= cos(angle) * speed * dt;
        velocity.y -= sin(angle) * speed * dt;
    }

    // ship will keep going after letting go of the key
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    sprite->setPosition(position);
    velocity.x *= 0.995f; // a cap for te velocity so we dont become insanley fast
    velocity.y *= 0.995f;
    // wrap around screen edges like asteroids do
    if (position.x < 0)   position.x = 800; // so we dont shoot offscreen 
    if (position.x > 800) position.x = 0;
    if (position.y < 0)   position.y = 600;
    if (position.y > 600) position.y = 0;
}

void Player::draw(RenderWindow& window) {
    window.draw(*sprite); // just drwa it on screen
}
void Player::shoot() {
    if (bulletCount >= 50) 
        return; // since we hhhave shot as many as we can and array is full
    float moveAngle = sprite->getRotation().asRadians() - 1.5708f; // for velocity direction
    float visualAngle = sprite->getRotation().asRadians();          // for sprite rotation
    bullets[bulletCount++] = new Bullet(position.x, position.y, moveAngle, visualAngle); // visual angle since thhhe way its opointing and mooving are diff
}

// UPDATE BULLETS
void Player::updateBullets(float dt) {
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i]) bullets[i]->update(dt);
    }
    // remove innactive ones
    int newCount = 0;
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] && bullets[i]->isActive())
            bullets[newCount++] = bullets[i];
        else { delete bullets[i]; bullets[i] = nullptr; }
    }
    bulletCount = newCount;
}
// to draw our bullets comming from the player
void Player::drawBullets(RenderWindow& window) {
    for (int i = 0; i < bulletCount; i++)
        if (bullets[i]) bullets[i]->draw(window); // drawing all bullets that are active
}
//adjust player heath after we take damage
void Player::takeDamage(int amount) {
    health -= amount;

    if (health < 0)
        health = 0;
}
//return the health of player
int Player::getHealth() {
    return health;
}
//give the health of the player
Vector2f Player::getPosition() {
    return position;
}
// GET BULLETS
int Player::getScore() { 
    return score; 
}
float Player::getSpriteDegrees() {
    return sprite->getRotation().asDegrees();
}
void Player::setHealth(int h) { 
    health = h; 
}
void Player::setScore(int s) {
    score = s; 
}
void Player::setRotation(float deg) { 
    sprite->setRotation(degrees(deg));
}
void Player::setSpriteDegrees(float deg) {
    sprite->setRotation(degrees(deg));
}
void Player::reset() {
    position = Vector2f(400.f, 300.f);
    velocity = Vector2f(0.f, 0.f);
    sprite->setPosition(position);
    sprite->setRotation(degrees(0.f));
    health = 3;
    score = 0;
}
Bullet* Player::getBullets(int i) {
    return bullets[i];
}
int Player::getBulletCount() { 
    return bulletCount;
}
Player::~Player() {
    for (int i = 0; i < 50; i++)
        delete bullets[i];
}