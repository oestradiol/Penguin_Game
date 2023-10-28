#pragma once

#include <string>

#include "Sprite.h"
#include "Being.h"
#include "PenguinCannon.h"

class PenguinBody : public Being {
public:
    static constexpr float ACCELERATION = 250;
    static constexpr float MAX_SPEED = 500;
    static constexpr float TURNING_SPEED = 250 * M_PI / 180;

    PenguinBody(GameObject& associated);
    ~PenguinBody();

    void Start() override;
    void Update(float dt) override;
    bool Is(const std::string& type) const override;

    void NotifyCollision(GameObject& other) override;

    GameObject& GetAssociated() const;

    static PenguinBody* player;

private:
    std::weak_ptr<GameObject> pcannon;
    float linearSpeed;
    float angle;
    Sprite* sprite;
};

inline bool PenguinBody::Is(const std::string& type) const {
    return type == "PenguinBody" || Being::Is(type);
}

inline GameObject& PenguinBody::GetAssociated() const {
    return associated;
}