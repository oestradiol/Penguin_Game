using namespace std;

#include "../core/headers/InputManager.h"
#include "../core/headers/Camera.h"
#include "headers/PostDeletionAction.h"
#include "headers/Face.h"

Face::Face(GameObject& associated)
    : Component(associated), hitpoints(30) { }

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        Component* postDeletionAction = associated.GetComponent("PostDeletionAction");
        if (postDeletionAction) {
            (*static_cast<PostDeletionAction*>(postDeletionAction))();
        } else {
            associated.Destroy();
        }
    }
}

void Face::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();
    pair<int, int> mousePos = Camera::GetMousePos();
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON) &&
        associated.box.Contains({ (int) mousePos.first, (int) mousePos.second })) {

        Damage(rand() % 10 + 10);
    }
}

void Face::Render() { }