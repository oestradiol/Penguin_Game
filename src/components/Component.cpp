#include "headers/Component.h"

Component::Component(GameObject& associated)
    : associated(associated), destroyRequested(false) {
    associated.AddComponent(this);
}

Component::~Component() { }