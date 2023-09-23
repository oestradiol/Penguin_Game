using namespace std;

#include "../core/headers/InputManager.h"
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
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && associated.box.Contains({ (float) inputManager.GetMouseX(), (float) inputManager.GetMouseY() }))
        Damage(rand() % 10 + 10);
}

void Face::Render() { }