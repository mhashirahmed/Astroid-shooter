#include "Player.h"
#include <cmath> // Needed later for sin() and cos()

// constructor for player
Player::Player() {
    texture.loadFromFile("assets/playership.png");// laod texture
    sprite.setTexture(texture); // every sprite should have texture so i set
    Vector2u size = texture.getSize(); // gives sie of sprite
    sprite.setOrigin(Vector2f((float)size.x / 2.f, (float)size.y / 2.f));// setting the center of rotation so that it rotates from the center of the sprite
    position = Vector2f(400.f, 300.f); // center of a 800x600 resolution
    sprite.setPosition(position); // set the position as the center

    speed = 150.f;
    rotation = 200.f;
    health = 3;
    score = 0;
    // intialized value(dummy forr now change later depending on feel)
}

// the actual physics part
void Player::update(float dt) {
    // 1. Write an 'if' statement checking the Left or A key.
    //    If pressed, rotate the sprite negatively using dt.
    if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left)) {
        sprite.rotate(degrees(-rotation * dt)); // in sfml 3 roatin must be in degrees
        // dt is delta time or change in time since last frame so we use in games so its same for all systems as were using seconds not frames
    }
    // checks if a or left arrow key pressed)

    if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right)) {
        sprite.rotate(degrees(rotation * dt));
    }// same code but for right rotation

    if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up)) {
        // We use .asRadians() because C++ math (sin/cos) requires radians
        float angle = sprite.getRotation().asRadians();
        velocity.x += cos(angle) * speed * dt;
        velocity.y += sin(angle) * speed * dt;
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down)) {
        float angle = sprite.getRotation().asRadians();
        velocity.x -= cos(angle) * speed * dt;
        velocity.y -= sin(angle) * speed * dt;
    }// subtract to move back add to move front

    // ship will keep going after letting go of the key
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    sprite.setPosition(position);

}

void Player::draw(RenderWindow& window) {
    window.draw(sprite); // just drwa it on screen
}
void Player::shoot() {

    float angle = sprite.getRotation().asRadians();

    Vector2f direction(
        cos(angle),
        sin(angle)
    );

    bullets.push_back(
        Bullet(position, direction)
    );
}

// UPDATE BULLETS
void Player::updateBullets(float dt) {

    for (auto& bullet : bullets) {
        bullet.update(dt);
    }

    // remove inactive bullets
    bullets.erase(
        remove_if(
            bullets.begin(),
            bullets.end(),

            [](Bullet& b) {
                return !b.isActive();
            }

        ),
        bullets.end()
    );
}
// to draw our bullets comming from the player
void Player::drawBullets(RenderWindow& window) {

    for (auto& bullet : bullets) {
        bullet.draw(window);
    }
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
vector<Bullet>& Player::getBullets() {
    return bullets;
}