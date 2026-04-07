#include "BattleState.h"
#include "GameManager.h"
#include "FieldMenu.h"
#include <DxLib.h>

void BattleState::update(GameManager& gm)
{
    gm.getBattleManager().update();
    gm.getFieldMenu().update(gm.getInput());
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

    gm.getFieldMenu().draw(gm.getDisplay());

    DrawFormatString(
        20, 20,
        GetColor(255, 255, 255),
        "[DEBUG]canShowFlg: %d",
        gm.getCanShow()
    );
}