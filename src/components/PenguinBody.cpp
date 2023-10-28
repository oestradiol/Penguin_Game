using namespace std;

#include "../core/headers/Game.h"
#include "../core/headers/InputManager.h"
#include "headers/PostDeletionAction.h"
#include "headers/PenguinBody.h"
#include "headers/Sprite.h"
#include "headers/Bullet.h"
#include "headers/Sound.h"

PenguinBody* PenguinBody::player = nullptr;
PenguinBody::PenguinBody(GameObject& associated)
    : Being(associated, 120), linearSpeed(0.0), angle(0.0) {
    sprite = new Sprite(associated, "assets/img/penguin.png");
    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    GameObject* go = new GameObject();
    new PenguinCannon(*go, Game::GetInstance().GetState().GetObjectPtr(&associated));
    pcannon = Game::GetInstance().GetState().AddObject(go);
}

void PenguinBody::Update(float dt) {
    if (InputManager::GetInstance().IsKeyPressed(SDLK_w)) {
        linearSpeed += ACCELERATION * dt;
    }
    if (InputManager::GetInstance().IsKeyPressed(SDLK_s)) {
        linearSpeed -= ACCELERATION * dt;
    }
    if (InputManager::GetInstance().IsKeyPressed(SDLK_a)) {
        angle -= TURNING_SPEED * dt;
        sprite->SetRotation(angle * 180 / M_PI);
    }
    if (InputManager::GetInstance().IsKeyPressed(SDLK_d)) {
        angle += TURNING_SPEED * dt;
        sprite->SetRotation(angle * 180 / M_PI);
    }

    linearSpeed = max(min(linearSpeed, MAX_SPEED), -MAX_SPEED);

    Vec2 newPos = associated.box.Center();
    newPos.x += linearSpeed * cos(angle) * dt;
    newPos.y += linearSpeed * sin(angle) * dt;

    associated.box.x = newPos.x - associated.box.w / 2;
    associated.box.y = newPos.y - associated.box.h / 2;

    if (hp <= 0) {
        GameObject* go = new GameObject();

        Sprite* sprite = new Sprite(*go, "assets/img/penguindeath.png", 5, .100, .5);
        Sound* sound = new Sound(*go, "assets/audio/boom.wav");
        *new PostDeletionAction(*go) += make_pair(
            new Action([go, sprite, sound]() {
                sprite->Destroy();
                sound->Play();
            }),
            new CanDeleteAction(bind(&Sound::IsPlaying, sound))
        );

        go->box.SetCenter(associated.box.Center());
        Game::GetInstance().GetState().AddObject(go);
        associated.Destroy();
    }
}

void PenguinBody::NotifyCollision(GameObject& other) {
    set<string> types { "Bullet" };
    types = other.HasComponentsOfTypes(types);

    for (auto type = types.begin(); type != types.end(); type++) {
        if (*type != "Bullet" ||
            !((Bullet*) other.GetComponent("Bullet"))->targetsPlayer)
            continue;

        hp -= 30;
        break;
    }
}