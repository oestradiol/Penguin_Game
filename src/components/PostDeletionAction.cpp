using namespace std;

#include "headers/PostDeletionAction.h"

PostDeletionAction::PostDeletionAction(GameObject& associated)
    : Component(associated), called(false) { }

void PostDeletionAction::operator+=(pair<Action*, CanDeleteAction*> action) {
    actions.emplace_back(action);
};

void PostDeletionAction::operator()() {
    size_t len = actions.size();
    for (size_t i = 0; i < len; i++) {
        size_t pos = len - i - 1;
        auto& action = actions[pos];
        (*action.first)();
    }

    called = true;
}

void PostDeletionAction::Update(float _) {
    if (!called) return;

    size_t len = actions.size();
    for (size_t i = 0; i < len; i++) {
        size_t pos = len - i - 1;
        auto& action = actions[pos];
        if ((*action.second)()) {
            return;
        };
    }

    associated.Destroy();
}