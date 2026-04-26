#include "GameObject.h"
// stting intial velocity as 0
GameObject::GameObject(): sprite(texture){ 
    position = Vector2f(0.f, 0.f);
    velocity = Vector2f(0.f, 0.f);
}
FloatRect GameObject::getBounds() const {
    return sprite.getGlobalBounds();
}