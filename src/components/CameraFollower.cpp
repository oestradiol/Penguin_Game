using namespace std;

#include "../core/headers/Camera.h"
#include "headers/CameraFollower.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) { }

void CameraFollower::Start() {
    started = true;
}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() { }