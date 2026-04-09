#pragma once
#include "IGameState.h"
#include <memory>

class BattleMenu;
class GameManager;

class BattleState : public IGameState
{
public:
    explicit BattleState(GameManager& gm);
    ~BattleState();
    void update(GameManager& gm) override;
    void draw(GameManager& gm) override;

private:
    std::unique_ptr<BattleMenu> battleMenu;
};