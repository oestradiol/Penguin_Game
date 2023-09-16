#define INCLUDE_SDL
#include "h_files/SDL_include.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
using namespace std;

#include "h_files/State.h"
#include "h_files/GameObject.h"
#include "h_files/Sprite.h"
#include "h_files/Sound.h"
#include "h_files/Face.h"
#include "h_files/PostDeletionAction.h"

State::State()
    : music("assets/audio/stageState.ogg"), quitRequested(false) {
    music.Play();

    LoadAssets();
}
State::~State() {
    objectArray.clear();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    // Initialize bg
    GameObject* go = new GameObject();
    go->box.x = 0;
    go->box.y = 0;

    new Sprite(*go, "assets/img/ocean.jpg");

    objectArray.emplace_back(go);
}

void State::Update(float dt) {
    Input();
    
    size_t len = objectArray.size() - 1;
    for (size_t i = 0; i <= len; i++) {
        size_t pos = len - i;
        if (!objectArray[pos]->IsDead()) {
            objectArray[pos]->Update(dt);
        } else {
            objectArray.erase(objectArray.begin() + pos);
        }
    }
}

void State::Render() {
    for (const auto& object : objectArray) {
        object->Render();
    }
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // Se o evento for quit, setar a flag para terminação
            case SDL_QUIT:
			    quitRequested = true;
                break;

            // Se o evento for clique...
            case SDL_MOUSEBUTTONDOWN:
            {
                // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
                size_t len = objectArray.size() - 1;
                for (size_t i = 0; i <= len; i++) {
                    size_t pos = len - i;
                    
                    // Obtem o ponteiro e casta pra Face.
                    GameObject* go = (GameObject*) objectArray[pos].get();
                    // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                    // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                    // ao usar get(), violamos esse princípio e estamos menos seguros.
                    // Esse código, assim como a classe Face, é provisório. Futuramente, para
                    // chamar funções de GameObjects, use objectArray[i]->função() direto.

                    if (go->box.Contains({ (float) mouseX, (float) mouseY })) {
                        Component* face = go->GetComponent("Face");
                        if (face) {
                            // Aplica dano
                            static_cast<Face*>(face)->Damage(rand() % 10 + 10);
                            // Sai do loop (só queremos acertar um)
                            break;
                        }
                    }
                }
                break;
            }

            case SDL_KEYDOWN:
                // Se a tecla for ESC, setar a flag de quit
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quitRequested = true;
                } else { // Se não, crie um objeto
                    Vec2 objPos = Vec2(200, 0).Rotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                    AddObject((int)objPos.x, (int)objPos.y);
                }
                break;
            
            default:
                break;
        }
	}
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* go = new GameObject();

    Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
    go->box.x = mouseX - go->box.w / 2;
    go->box.y = mouseY - go->box.h / 2;

    Face* face = new Face(*go);
    Sound* sound = new Sound(*go, "assets/audio/boom.wav");

    PostDeletionAction* afterDelete = new PostDeletionAction(*go);
    *afterDelete += make_pair(
        new Action([go, sprite, face, sound]() {
            go->RemoveComponent(sprite);
            go->RemoveComponent(face);
            sound->Play();
        }),
        new CanDeleteAction(std::bind(&Sound::IsPlaying, sound))
    );

    objectArray.emplace_back(go);
}