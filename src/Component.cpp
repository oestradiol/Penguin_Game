#include "h_files/Component.h"

Component::~Component() { }

Component::Component(GameObject& associated) : associated(associated) { }