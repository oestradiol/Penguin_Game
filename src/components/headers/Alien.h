#pragma once

#include <queue>
#include <vector>
#include <memory>

#include "../../utils/headers/Vec2.h"
#include "Component.h"

#define ALIEN_SPEED 300

class GameObject;

class Alien : public Component {
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    bool Is(const std::string& type) const override;

private:
    class Action {
    public:
        enum ActionType { MOVE, SHOOT };

        Action(ActionType type, float x, float y);

        ActionType type;
        Vec2 pos;
    };

    int nMinions;
    Vec2 speed;
    int hp;

    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
};

inline bool Alien::Is(const string& type) const {
    return type == "Alien";
}