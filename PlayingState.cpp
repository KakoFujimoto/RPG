#include "PlayingState.h"
#include "GameManager.h"
#include "FieldMenu.h"
#include <DxLib.h>

PlayingState::PlayingState(GameManager& gm)
{
    fieldMenu = std::make_unique<FieldMenu>(
        &gm,
        gm.getDisplay(),
        gm.getAlly().getParameter()
    );
}

PlayingState::~PlayingState() = default;

void PlayingState::update(GameManager& gm)
{
    gm.updateItemBag();
    gm.checkEncount();

    const Input& input = gm.getInput();

    fieldMenu->update(gm.getInput());

    if (!fieldMenu->getIsOpen())
    {
        gm.getAlly().move(input);
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

    fieldMenu->draw(gm.getDisplay());

    gm.getFieldEnemyManager().draw();
    gm.getFieldItemManager().draw();
}