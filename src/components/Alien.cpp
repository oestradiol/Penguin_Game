using namespace std;

#include "../core/headers/Game.h"
#include "../core/headers/InputManager.h"
#include "../core/headers/Camera.h"
#include "headers/Alien.h"
#include "headers/Minion.h"
#include "headers/Sprite.h"

Alien::Alien(GameObject& associated, int nMinions)
    : Component(associated), nMinions(nMinions), speed(0, 0), hp(30) {
    new Sprite(associated, "assets/img/alien.png");
}

Alien::~Alien() {
    minionArray.clear();
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
    InputManager& inputManager = InputManager::GetInstance();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        pair<int, int> target = Camera::GetMousePos();
        Action action = Action(Action::ActionType::SHOOT, target.first, target.second);
        taskQueue.push(action);
    } else if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        pair<int, int> target = Camera::GetMousePos();
        Action action = Action(Action::ActionType::MOVE, target.first, target.second);
        taskQueue.push(action);
    }

    if (!taskQueue.empty()) {
        Action action = taskQueue.front();
        if (action.type == Action::ActionType::MOVE) {
            Vec2 center = associated.box.Center();

            Vec2 direction = Vec2(action.pos.x - center.x, action.pos.y - center.y).Normalized();
            speed = direction * ALIEN_SPEED;

            if (center.Distance(action.pos) < ALIEN_SPEED * dt) {
                associated.box.SetCenter(action.pos);
                speed = Vec2(0, 0);
                taskQueue.pop();
            }
        } else  if (action.type == Action::ActionType::SHOOT) {
            shared_ptr<GameObject> minionObj = minionArray[0].lock();
            for (size_t i = 1; i < minionArray.size(); i++) {
                shared_ptr<GameObject> go = minionArray[i].lock();
                if (go->box.Center().Distance(action.pos) < minionObj->box.Center().Distance(action.pos)) {
                    minionObj = go;
                }
            }

            Minion* minion = static_cast<Minion*>(minionObj->GetComponent("Minion"));
            minion->Shoot(action.pos);
            taskQueue.pop();
        }
    }

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    Sprite* sprite = static_cast<Sprite*>(associated.GetComponent("Sprite"));
    sprite->SetRotation(sprite->GetRotation() - dt * ALIEN_SPEED / 5);

    if (hp <= 0) {
        associated.Destroy();
    }
}

void Alien::Render() { }

Alien::Action::Action(ActionType type, float x, float y) : type(type), pos(x, y) { }