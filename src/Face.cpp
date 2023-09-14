using namespace std;

#include "h_files/Face.h"
#include "h_files/Sound.h"

Face::Face(GameObject& associated)
    : Component(associated), hitpoints(30) { }

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        Component* sound = associated.GetComponent("Sound");
        if (sound) {
            static_cast<Sound*>(sound)->Play();
        }
    }
}

void Face::Update(float dt) { }

void Face::Render() { }

bool Face::Is(const string& type) const {
    return (type == "Face");
}
