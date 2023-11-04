#include "Engine/core/headers/Game.h"
#include "Penguin/stages/headers/TitleState.h"

int main (int argc, char** argv) {
    Game& game = Game::GetInstance();
    game.Push((State*) new TitleState());

    game.Run();

    delete &game;

    return 0;
}