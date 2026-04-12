#include "BattleState.h"
#include "GameManager.h"
#include "BattleMenu.h"
#include <DxLib.h>

BattleState::BattleState(GameManager& gm)
{
    auto& bm = gm.getBattleManager();
    bm.reset();

    auto& enemy = gm.getEnemy();
    gm.getBattleWindowRenderer().setMessage(
        enemy.getName() + " が あらわれた！"
    );

    battleMenu = std::make_unique<BattleMenu>(
        &gm,
        &gm.getBattleManager(),
        gm.getDisplay(),
        gm.getAlly().getParameter(),
        &gm.getItemBag()
    );
}

BattleState::~BattleState() = default;

void BattleState::update(GameManager& gm)
{
    auto& bm = gm.getBattleManager();
    bm.update();

    if (gm.hasPendingStateChange())
    {
        return;
    }

    if (bm.isWin())
    {
        gm.requestStateChange(GameManager::GameState::Playing);
        return;
    }

    if (bm.isLose())
    {
        gm.requestStateChange(GameManager::GameState::GameOver);
        return;
    }

    if (bm.isEscapeFinished())
    {
        gm.requestStateChange(GameManager::GameState::Playing);
        return;
    }

    battleMenu->update(gm.getInput());
}

void BattleState::draw(GameManager& gm)
{
    int bgColor = GetColor(0, 140, 0);
    DrawBox(0, 0, 800, 600, bgColor, TRUE);

    DrawString(
        gm.getAlly().getX(),
        gm.getAlly().getY(),
        gm.getAlly().getName().c_str(),
        GetColor(255, 255, 255)
    );

    DrawFormatString(
        20, 20,
        GetColor(255, 255, 255),
        "[DEBUG]canShowFlg: %d",
        gm.getCanShow()
    );

    battleMenu->draw();
}