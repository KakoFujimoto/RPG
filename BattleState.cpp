#include "BattleState.h"
#include "GameManager.h"
#include "BattleMenu.h"
#include <DxLib.h>

BattleState::BattleState(GameManager& gm)
{
    gm.getBattleManager().reset();

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
    gm.getBattleManager().update();
    if (gm.hasPendingStateChange())
    {
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