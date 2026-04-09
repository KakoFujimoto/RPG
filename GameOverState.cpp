#include "GameOverState.h"
#include "GameManager.h"
#include <DxLib.h>

void GameOverState::update(GameManager& gm)
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        gm.changeState(GameManager::GameState::Playing);
    }
}

void GameOverState::draw(GameManager& gm)
{
    int bgColor = GetColor(0, 0, 0);
    DrawBox(0, 0, 800, 600, bgColor, TRUE);

    DrawString(320, 260, "GAME OVER", GetColor(255, 0, 0));
    DrawString(250, 300, "Press Enter to return to Playing", GetColor(255, 255, 255));
}