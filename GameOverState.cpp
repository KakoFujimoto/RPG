#include "GameOverState.h"
#include "GameManager.h"
#include "PlayingState.h"
#include "BattleState.h"

void GameOverState::update(GameManager& gm)
{
    // 現時点では更新処理なし
}

void GameOverState::draw(GameManager& gm)
{
    if (gm.isBattle())
    {
        BattleState battleState;
        battleState.draw(gm);
        return;
    }

    PlayingState playingState;
    playingState.draw(gm);
}