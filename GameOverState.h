#pragma once
#include "IGameState.h"

class GameOverState : public IGameState
{
public:
    void update(GameManager& gm) override;
    void draw(GameManager& gm) override;
};