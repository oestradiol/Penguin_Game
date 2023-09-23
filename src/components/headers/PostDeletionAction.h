#pragma once

#include <functional>

#include "Component.h"

typedef std::function<void()> Action;
typedef std::function<bool()> CanDeleteAction;

class PostDeletionAction : public Component {
public:
    PostDeletionAction(GameObject& associated);

    void operator+=(std::pair<Action*, CanDeleteAction*> action);
    void operator()();

    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;

private:
    std::vector< std::pair< std::unique_ptr<Action>, std::shared_ptr<CanDeleteAction> > > actions;
    bool called;
};

inline bool PostDeletionAction::Is(const string& type) const {
    return type == "PostDeletionAction";
}