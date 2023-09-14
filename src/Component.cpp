#include "h_files/Component.h"

Component::Component(GameObject& associated)
    : associated(associated) {
    associated.AddComponent(this);
}

Component::~Component() { }