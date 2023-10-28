#pragma once

#include <queue>
#include <vector>
#include <memory>

#include "../../utils/headers/Vec2.h"
#include "Component.h"

class GameObject;

class Being : public Component {
public:
    Being(GameObject& associated, int hp);

    void NotifyCollision(GameObject& other) override;

    bool Is(const std::string& type) const override;

protected:
    Vec2 speed;
    int hp;
};

inline bool Being::Is(const std::string& type) const {
    return type == "Being";
}