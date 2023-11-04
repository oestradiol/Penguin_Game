#pragma once

#include <string>

#include "../../core/headers/GameObject.h"

class Component {
public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Start();
    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(const std::string& type) const = 0;
    
    virtual void NotifyCollision(GameObject& other);

    void Destroy();
    bool IsDestroyed();

protected:
    GameObject& associated;
    bool destroyRequested;
    bool started;
};

inline void Component::Start() {
    started = true;
}

inline void Component::Update(float dt) { }

inline void Component::Render() { }

inline void Component::Destroy() {
    destroyRequested = true;
}

inline bool Component::IsDestroyed() {
    return destroyRequested;
}

inline void Component::NotifyCollision(GameObject& other) { }