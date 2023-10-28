#pragma once

#include <queue>
#include <vector>
#include <memory>

#include "../../utils/headers/Vec2.h"
#include "Being.h"

class GameObject;

class Alien : public Being {
public:
    static constexpr float SPEED = 150;
    static constexpr int COOLDOWN_TIME = 1;
    static int alienCount;

    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start() override;
    void Update(float dt) override;

    void NotifyCollision(GameObject& other) override;

    bool Is(const std::string& type) const override;

private:
    enum AlienState { MOVING, RESTING };
    int nMinions;
    AlienState state;
    Timer restTimer;
    Vec2 destination; 
    std::vector<std::weak_ptr<GameObject>> minionArray;
};

inline bool Alien::Is(const std::string& type) const {
    return type == "Alien" || Being::Is(type);
}