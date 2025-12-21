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
    drawMonster();
    drawMessage();
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

    int infoX = x + width - 260;
    int infoY = y + 20;
    int infoW = 240;
    int infoH = 60;

    DrawBox(
        infoX, infoY,
        infoX + infoW, infoY + infoH,
        GetColor(0, 0, 0),
        TRUE
    );

    DrawBox(
        infoX, infoY,
        infoX + infoW, infoY + infoH,
        GetColor(255, 255, 255),
        FALSE
    );

    DrawString(
        infoX + 10,
        infoY + 20,
        text.c_str(),
        GetColor(255, 255, 255)
    );
}

void BattleWindowRenderer::setBattleInfo(const BattleStartInfo* info)
{
    battleInfo = info;
}
void BattleWindowRenderer::drawMessage()
{
    if (!battleInfo)
    {
        return;
    }

    std::string message =
        battleInfo->enemyName + "‚ª‚ ‚ç‚í‚ê‚½I";

    int msgX = x + 20;
    int msgY = y + height - 100;
    int msgW = width - 40;
    int msgH = 80;

    DrawBox(
        msgX, msgY,
        msgX + msgW, msgY + msgH,
        GetColor(0, 0, 0),
        TRUE
    );

    DrawBox(
        msgX, msgY,
        msgX + msgW, msgY + msgH,
        GetColor(255, 255, 255),
        FALSE
    );

    DrawString(
        msgX + 10,
        msgY + 20,
        message.c_str(),
        GetColor(255, 255, 255)
    );
}
void BattleWindowRenderer::drawMonster()
{
    if (!battleInfo)
    {
        return;
    }

    int areaX = x + 100;
    int areaY = y + 100;
    int areaW = width - 200;
    int areaH = height - 250;

    const std::string& name = battleInfo->enemyName;

    int textWidth = static_cast<int>(name.size()) * 16;
    int textHeight = 16;

    int textX = areaX + (areaW - textWidth) / 2;
    int textY = areaY + (areaH - textHeight) / 2;

    DrawString(
        textX,
        textY,
        name.c_str(),
        GetColor(255, 255, 255)
    );
}