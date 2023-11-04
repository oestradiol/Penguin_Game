#include "headers/Component.h"

Component::Component(GameObject& associated)
    : associated(associated), destroyRequested(false), started(false) {
    associated.AddComponent(this);
}

Component::~Component() { }