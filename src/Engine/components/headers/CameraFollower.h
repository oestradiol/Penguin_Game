#pragma once

#include "Component.h"
#include "../../utils/headers/Vec2.h"

class CameraFollower : public Component {
public:
    CameraFollower(GameObject& go);
    
    void Update(float dt) override;
    bool Is(const std::string& type) const override;
};

inline bool CameraFollower::Is(const std::string& type) const {
    return type == "CameraFollower";
}