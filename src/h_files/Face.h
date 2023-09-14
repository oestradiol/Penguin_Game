#pragma once

#include "Component.h"
#include "GameObject.h"

class Face : public Component {
public:
    Face(GameObject& associated);

    void Damage(int damage);

    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;

private:
    int hitpoints;
};