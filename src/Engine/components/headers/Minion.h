#pragma once

#include <string>
#include <memory>

#include "Component.h"

class Minion : public Component {
public:
    static constexpr float MINION_SPEED = 100.0;

    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

    void Update(float dt) override;
    
    bool Is(const std::string& type) const override;

    void Shoot(Vec2 target);

private:
    void UpdatePos(shared_ptr<GameObject>& centerPtr);
    void UpdateRot(shared_ptr<GameObject>& centerPtr);

    std::weak_ptr<GameObject> alienCenter;
    float arcDeg;
};

inline bool Minion::Is(const std::string& type) const {
    return type == "Minion";
}