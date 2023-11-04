#pragma once

#include <string>

#include "Component.h"

class Bullet : public Component {
public:
    static constexpr int SPEED = 750;
    static constexpr int DAMAGE = 10;
    static constexpr int MAX_DISTANCE = 2880;
    
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& sprite, int frameCount = 1, float frameTime = 1, bool targetsPlayer = true);

    void Update(float dt) override;
    
    bool Is(const std::string& type) const override;

    void NotifyCollision(GameObject& other) override;
    
    int GetDamage() const;
    
    bool targetsPlayer;

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

inline bool Bullet::Is(const std::string& type) const {
    return type == "Bullet";
}