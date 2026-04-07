#include "PlayingState.h"
#include "GameManager.h"
#include "FieldMenu.h"
#include <DxLib.h>

void PlayingState::update(GameManager& gm)
{
    gm.updateItemBag();
    gm.checkEncount();

    gm.getFieldMenu().update(gm.getInput());

    if (!gm.isBattle() && !gm.getFieldMenu().getIsOpen())
    {
        gm.getAlly().move();
    }
}

void PlayingState::draw(GameManager& gm)
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

    gm.getFieldEnemyManager().draw();
    gm.getFieldItemManager().draw();
}