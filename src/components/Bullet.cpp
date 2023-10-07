using namespace std;

#include "headers/Bullet.h"
#include "headers/Sprite.h"

#include <iostream>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& sprite)
    : Component(associated), speed(speed, 0), distanceLeft(maxDistance), damage(damage) {
    Sprite* spriteComponent = new Sprite(associated, sprite);
    spriteComponent->SetRotation(angle * 180.0 / M_PI);
    this->speed = this->speed.Rotated(angle);
}

void Bullet::Start() { }

void Bullet::Update(float dt) {
    Vec2 movement = speed * dt;
    associated.box += movement;
    distanceLeft -= movement.Magnitude();
    if (distanceLeft <= 0) {
        associated.Destroy();
    }
}

void Bullet::Render() { }

int Bullet::GetDamage() {
    return damage;
}
