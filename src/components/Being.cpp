using namespace std;

#include "headers/Being.h"
#include "headers/Collider.h"

Being::Being(GameObject& associated, int hp)
    : Component(associated), speed(0, 0), hp(hp) {
    new Collider(associated);
}

void Being::NotifyCollision(GameObject& other) {
    set<string> types { "Bullet" };
    types = other.HasComponentsOfTypes(types);

    for (auto type = types.begin(); type != types.end(); type++) {
        if (*type != "Bullet") continue;
        hp -= 30;
        break;
    }
}