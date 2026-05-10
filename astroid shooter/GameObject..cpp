#include "GameObject.h"
// stting intial velocity as 0
GameObject::GameObject(){ 
    position = Vector2f(0.f, 0.f);
    velocity = Vector2f(0.f, 0.f);
}
FloatRect GameObject::getBounds() const {
    return sprite->getGlobalBounds();
}
Vector2f GameObject::getVelocity() const { 
    return velocity; 
}
void GameObject::setVelocity(Vector2f vel) {
    velocity = vel; 
}
void GameObject::setPosition(Vector2f pos) {
    position = pos;
    sprite->setPosition(pos);
}
GameObject::~GameObject() {
    delete sprite;
}