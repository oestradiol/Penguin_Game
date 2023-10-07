#pragma once

#include <string>

#include "Component.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& sprite);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    
    bool Is(const std::string& type) const override;

    int GetDamage();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

inline bool Bullet::Is(const std::string& type) const {
    return type == "Bullet";
}