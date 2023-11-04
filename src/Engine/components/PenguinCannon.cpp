using namespace std;

#include "../core/headers/Game.h"
#include "../core/headers/InputManager.h"
#include "../core/headers/Camera.h"
#include "headers/PenguinCannon.h"
#include "headers/Bullet.h"
#include "headers/Sprite.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) : Component(associated), pbody(penguinBody), angle(0.0) {
    sprite = new Sprite(associated, "assets/img/cubngun.png");
}

void PenguinCannon::Update(float dt) {
    shared_ptr<GameObject> penguinBodyPtr = pbody.lock();
    if (!penguinBodyPtr) {
        associated.Destroy();
        return;
    }

    associated.box.x = penguinBodyPtr->box.Center().x - associated.box.w / 2;
    associated.box.y = penguinBodyPtr->box.Center().y - associated.box.h / 2;

    pair<int, int> pos = Camera::GetMousePos();
    angle = (Vec2(pos.first, pos.second) - associated.box.Center()).Angle();
    sprite->SetRotation(angle * 180 / M_PI);

    if (InputManager::GetInstance().WasMousePressed(LEFT_MOUSE_BUTTON) &&
        timer.Get() >= COOLDOWN_TIME) {
        Shoot();
        timer.Restart();
    } else {
        timer.Update(dt);
    }
}

void PenguinCannon::Shoot() {
    GameObject* go = new GameObject();
    new Bullet(*go, angle, Bullet::SPEED, Bullet::DAMAGE, Bullet::MAX_DISTANCE, "assets/img/penguinbullet.png", 1, 1.0F, false);
    go->box.SetCenter(associated.box.Center() + Vec2(CANNON_DISTANCE, 0).Rotated(angle));
    Game::GetInstance().GetCurrentState().AddObject(go);
}
