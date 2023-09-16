#pragma once

#include <functional>

#include "Component.h"
#include "GameObject.h"

typedef std::function<void()> Action;
typedef std::function<bool()> CanDeleteAction;

class PostDeletionAction : public Component {
public:
    PostDeletionAction(GameObject& associated);

    void operator+=(std::pair<Action*, CanDeleteAction*> action);
    void RequestDelete();

    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;

private:
    std::vector< std::pair< std::unique_ptr<Action>, std::shared_ptr<CanDeleteAction> > > actions;
    bool isDeleteRequested;
};