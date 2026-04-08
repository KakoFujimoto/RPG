#pragma once
#include "IGameState.h"
#include <memory>

class FieldMenu;

class PlayingState : public IGameState
{
public:
    explicit PlayingState(GameManager& gm);
    ~PlayingState();
    void update(GameManager& gm) override;
    void draw(GameManager& gm) override;

private:
    std::unique_ptr<FieldMenu> fieldMenu;
};