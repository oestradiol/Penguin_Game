#pragma once

#include <string>

#include "../../utils/headers/Timer.h"

#include "Component.h"

class PenguinCannon : public Component {
public:
    static constexpr int CANNON_DISTANCE = 100;
    static constexpr int COOLDOWN_TIME = 1;
    PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
    
    void Update(float dt) override;
    bool Is(const std::string& type) const override;

    void Shoot();

private:
    std::weak_ptr<GameObject> pbody;
    float angle;
    Timer timer;
    Sprite* sprite;
};

inline bool PenguinCannon::Is(const std::string& type) const {
    return type == "PenguinCannon";
}