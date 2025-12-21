#include"BattleWindowRenderer.h"
#include"DxLib.h"
#include"BattleStartInfo.h"

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

    drawEnemyInfo();
}
void BattleWindowRenderer::drawEnemyInfo()
{
    if (!battleInfo)
    {
        return;
    }

    std::string text =
        battleInfo->enemyName + " - " +
        std::to_string(battleInfo->count) + "‚Ð‚«";

    DrawString(
        x + width - 220,
        y + 20,
        text.c_str(),
        GetColor(255, 255, 255)
    );
}
void BattleWindowRenderer::setBattleInfo(const BattleStartInfo* info)
{
    battleInfo = info;
}