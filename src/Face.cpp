using namespace std;

#include "h_files/Face.h"
#include "h_files/PostDeletionAction.h"

Face::Face(GameObject& associated)
    : Component(associated), hitpoints(30) { }

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        Component* postDeletionAction = associated.GetComponent("PostDeletionAction");
        if (postDeletionAction) {
            static_cast<PostDeletionAction*>(postDeletionAction)->RequestDelete();
        } else {
            associated.RequestDelete();
        }
    }
}

void Face::Update(float dt) { }

void Face::Render() { }

bool Face::Is(const string& type) const {
    return (type == "Face");
}
