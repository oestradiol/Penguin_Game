#pragma once

#include <string>

#include "GameObject.h"

class Component {
public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(const std::string& type) const = 0;

protected:
    GameObject& associated;
};