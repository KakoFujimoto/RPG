#include "BattleWindowRenderer.h"
#include "DxLib.h"

BattleWindowRenderer::BattleWindowRenderer(Display& d)
    : display(d)
{
}

void BattleWindowRenderer::setPosition(int px, int py)
{
    x = px;
    y = py;
}

void BattleWindowRenderer::setSize(int w, int h)
{
    width = w;
    height = h;
}

void BattleWindowRenderer::draw()
{
    DrawBox(
        x, y,
        x + width, y + height,
        GetColor(0, 0, 0),
        TRUE
    );

    DrawBox(
        x, y,
        x + width, y + height,
        GetColor(255, 255, 255),
        FALSE
    );
}