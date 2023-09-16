using namespace std;

#include "h_files/PostDeletionAction.h"

PostDeletionAction::PostDeletionAction(GameObject& associated)
    : Component(associated), isDeleteRequested(false) { }

void PostDeletionAction::operator+=(std::pair<Action*, CanDeleteAction*> action) {
    actions.emplace_back(action);
};

void PostDeletionAction::RequestDelete() {
    size_t len = actions.size() - 1;
    for (size_t i = 0; i <= len; i++) {
        size_t pos = len - i;
        auto& action = actions[pos];
        (*action.first)();
    }

    isDeleteRequested = true;
}

void PostDeletionAction::Update(float _) {
    if (!isDeleteRequested) return;

    size_t len = actions.size() - 1;
    for (size_t i = 0; i <= len; i++) {
        size_t pos = len - i;
        auto& action = actions[pos];
        if ((*action.second)()) {
            return;
        };
    }

    associated.RequestDelete();
}

void PostDeletionAction::Render() { }

bool PostDeletionAction::Is(const string& type) const {
    return type == "PostDeletionAction";
}