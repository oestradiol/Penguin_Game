using namespace std;

#include "headers/Minion.h"
#include "headers/Sprite.h"
#include "headers/Collider.h"
#include "headers/Bullet.h"
#include "../core/headers/Game.h"
#include "../core/headers/InputManager.h"
#include "../core/headers/Camera.h"
#include "../utils/headers/Vec2.h"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) 
    : Component(associated), alienCenter(alienCenter), arcDeg(arcOffsetDeg) {
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    float randomScale = 1.0f + 0.5f * (float) rand() / (float) RAND_MAX;
    sprite->SetScale(randomScale, randomScale);

    new Collider(associated);

    shared_ptr<GameObject> centerPtr = alienCenter.lock();
    UpdatePos(centerPtr);
}

void Minion::Update(float dt) {
    arcDeg += MINION_SPEED * dt;

    shared_ptr<GameObject> centerPtr = alienCenter.lock();
    if (!centerPtr) {
        associated.Destroy();
        return;
    }

    UpdatePos(centerPtr);
    UpdateRot(centerPtr);
}

void Minion::UpdatePos(shared_ptr<GameObject>& centerPtr) {
    float radianOffset = arcDeg * M_PI / 180.0;
    Vec2 centerPos = Vec2(200.0, 0.0).Rotated(radianOffset) + centerPtr->box.Center();
    associated.box.SetCenter(centerPos);
}

void Minion::UpdateRot(shared_ptr<GameObject>& centerPtr) {
    Vec2 alienPos = centerPtr->box.Center();
    Vec2 minionPos = associated.box.Center();
    double angleDeg = Vec2::AngleBetween(minionPos, alienPos) * 180.0 / M_PI;
    static_cast<Sprite*>(associated.GetComponent("Sprite"))->SetRotation(angleDeg);
}

void Minion::Shoot(Vec2 pos) {
    GameObject* go = new GameObject();
    float angle = (pos - associated.box.Center()).Angle();
    new Bullet(*go, angle, Bullet::SPEED, Bullet::DAMAGE, Bullet::MAX_DISTANCE, "assets/img/minionbullet2.png", 3, .25);
    go->box.SetCenter(associated.box.Center());
    Game::GetInstance().GetCurrentState().AddObject(go);
}