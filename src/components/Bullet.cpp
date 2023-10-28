using namespace std;

#include "headers/Bullet.h"
#include "headers/Sprite.h"
#include "headers/Collider.h"

#include <iostream>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const string& sprite, int frameCount, float frameTime, bool targetsPlayer)
    : Component(associated), targetsPlayer(targetsPlayer), speed(speed, 0), distanceLeft(maxDistance), damage(damage) {
    Sprite* spriteComponent = new Sprite(associated, sprite, frameCount, frameTime);
    spriteComponent->SetRotation(angle * 180.0 / M_PI);

    new Collider(associated);
    
    this->speed = this->speed.Rotated(angle);
}

void Bullet::Update(float dt) {
    Vec2 movement = speed * dt;
    associated.box += movement;
    distanceLeft -= movement.Magnitude();
    if (distanceLeft <= 0) {
        associated.Destroy();
    }
}

int Bullet::GetDamage() const {
    return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
    string target = this->targetsPlayer ? "PenguinBody" : "Alien";
    set<string> types { target };
    types = other.HasComponentsOfTypes(types);
    
    for (auto type = types.begin(); type != types.end(); type++) {
        if (*type != target ||
            (!this->targetsPlayer && other.GetComponent("PenguinBody")) ||
            (this->targetsPlayer && other.GetComponent("Alien")))
            continue;
        associated.Destroy();
        break;
    }
}