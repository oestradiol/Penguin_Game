#pragma once

#include <string>

#include "../../core/headers/GameObject.h"

class Component {
public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Start() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(const std::string& type) const = 0;

    void Destroy();
    bool IsDestroyed();

protected:
    GameObject& associated;
    bool destroyRequested;
    bool started;
};

inline void Component::Destroy() {
    destroyRequested = true;
}

inline bool Component::IsDestroyed() {
    return destroyRequested;
}