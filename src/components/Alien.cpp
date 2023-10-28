using namespace std;

#include "../core/headers/Game.h"
#include "../core/headers/InputManager.h"
#include "../core/headers/Camera.h"
#include "headers/PostDeletionAction.h"
#include "headers/PenguinBody.h"
#include "headers/Collider.h"
#include "headers/Alien.h"
#include "headers/Sound.h"
#include "headers/Minion.h"
#include "headers/Sprite.h"
#include "headers/Bullet.h"

int Alien::alienCount = 0;
Alien::Alien(GameObject& associated, int nMinions)
    : Being(associated, 240), nMinions(nMinions), state(RESTING) {
    new Sprite(associated, "assets/img/alien.png");
    alienCount++;
}

Alien::~Alien() {
    minionArray.clear();
    alienCount--;
}

void Alien::Start() {
    State& state = Game::GetInstance().GetState();
    float offset = 360.0f / (float) nMinions;
    for (int i = 0; i < nMinions; i++) {
        GameObject* minionObject = new GameObject();
        new Minion(*minionObject, state.GetObjectPtr(&associated), offset * i);
        minionArray.push_back(state.AddObject(minionObject));
    }
}

void Alien::Update(float dt) {
    switch (state) {
        case RESTING:
            if (restTimer.Get() >= COOLDOWN_TIME) {
                restTimer.Restart();

                if (PenguinBody::player) {
                    destination = PenguinBody::player->GetAssociated().box.Center();
                    state = MOVING;
                }
            } else {
                restTimer.Update(dt);
            }
            break;

        case MOVING:
            Vec2 center = associated.box.Center();
            Vec2 direction = Vec2(destination.x - center.x, destination.y - center.y).Normalized();
            speed = direction * SPEED;

            if (center.Distance(destination) < SPEED * dt) {
                associated.box.SetCenter(destination);
                speed = Vec2(0, 0);

                shared_ptr<GameObject> minionObj = minionArray[0].lock();
                size_t len = minionArray.size();
                for (size_t i = 1; i < len; i++) {
                    shared_ptr<GameObject> go = minionArray[i].lock();
                    if (go->box.Center().Distance(destination) < minionObj->box.Center().Distance(destination)) {
                        minionObj = go;
                    }
                }
                Minion* minion = static_cast<Minion*>(minionObj->GetComponent("Minion"));
                minion->Shoot(destination);

                state = RESTING;
            }
            break;
    }

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    Sprite* sprite = static_cast<Sprite*>(associated.GetComponent("Sprite"));
    sprite->SetRotation(sprite->GetRotation() - dt * SPEED / 5);

    if (hp <= 0) {
        GameObject* go = new GameObject();

        Sprite* sprite = new Sprite(*go, "assets/img/aliendeath.png", 5, .100, .5);
        Sound* sound = new Sound(*go, "assets/audio/boom.wav");
        *new PostDeletionAction(*go) += make_pair(
            new Action([sprite, sound]() {
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

void Alien::NotifyCollision(GameObject& other) {
    set<string> types { "Bullet" };
    types = other.HasComponentsOfTypes(types);

    for (auto type = types.begin(); type != types.end(); type++) {
        if (*type != "Bullet" ||
            ((Bullet*) other.GetComponent("Bullet"))->targetsPlayer)
            continue;

        hp -= 30;
        break;
    }
}