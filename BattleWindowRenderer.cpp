#include"BattleWindowRenderer.h"
#include"DxLib.h"
#include"BattleStartInfo.h"
#include"ItemWindowRenderer.h"

BattleWindowRenderer::BattleWindowRenderer(Display& d)
    : display(d), allyStatusRenderer(d)
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

    drawAllyStatus();
    drawEnemyInfo();
    drawMonster();
    if (GetNowCount() - battleStartFrame >= 1000)
    {
        drawMenu();
    }
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
        std::to_string(battleInfo->count) + "Ç–Ç´";

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

    if (battleStartFrame < 0)
    {
        battleStartFrame = GetNowCount();
    }
}

void BattleWindowRenderer::drawMessage()
{
    std::string message;

    if (!currentMessage.empty())
    {
        message = currentMessage;
    }
    else if (battleInfo)
    {
        message = battleInfo->enemyName + "Ç™Ç†ÇÁÇÌÇÍÇΩÅI";
    }
    else
    {
        return;
    }

    int msgH = 80;
    int msgW = static_cast<int>(width * 0.70);

    int msgX = x + width - msgW - 20;
    int msgY = y + height - msgH - 20;

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
void BattleWindowRenderer::setAllyParameter(const AllyParameter* ally)
{
    allyParam = ally;
    allyStatusRenderer.setTarget(ally);
}
void BattleWindowRenderer::drawAllyStatus()
{
    if (!allyParam)
    {
        return;
    }

    int statusX = x + 20;
    int statusY = y + 20;

    allyStatusRenderer.setMode(StatusViewMode::BattleParameter);
    allyStatusRenderer.setPosition(statusX, statusY);
    allyStatusRenderer.draw();
}

void BattleWindowRenderer::drawMenu()
{
    int menuX = x + 20;
    int menuY = y + height - 100;
    int menuW = static_cast<int>(width * 0.25);
    int menuH = 80;

    DrawBox(
        menuX, menuY,
        menuX + menuW, menuY + menuH,
        GetColor(0, 0, 0),
        TRUE
    );

    DrawBox(
        menuX, menuY,
        menuX + menuW, menuY + menuH,
        GetColor(255, 255, 255),
        FALSE
    );

    int textX = menuX + 25;
    int textY = menuY + 10;
    int lineHeight = 14;
    int cursorColor = GetColor(255, 255, 255);

    for (int i = 0; i < static_cast<int>(battleMenuItems.size()); ++i)
    {
        int itemY = textY + i * lineHeight;

        if (i == selectedMenuIndex)
        {
            display.drawCursor(menuX + 5, itemY, cursorColor);
        }

        DrawString(
            textX,
            itemY,
            battleMenuItems[i].c_str(),
            GetColor(255, 255, 255)
        );
    }
}

int BattleWindowRenderer::getMenuCount() const
{
    return static_cast<int>(battleMenuItems.size());
}

void BattleWindowRenderer::prepareItemWindow(ItemWindowRenderer& itemRenderer)
{
    int msgH = 80;
    int msgW = static_cast<int>(width * 0.70);

    int msgX = x + width - msgW - 20;
    int msgY = y + height - msgH - 20;

    // è≠ÇµÇæÇØÇ∏ÇÁÇ∑(èdÇ»Ç¡ÇƒÇ¢ÇÈÇ∆ï™Ç©ÇÈíˆìx)
    int offsetX = -10;
    int offsetY = -10;

    itemRenderer.setPosition(
        msgX + offsetX,
        msgY + offsetY
    );
}
void BattleWindowRenderer::setMessage(const std::string& msg)
{
    currentMessage = msg;
}
void BattleWindowRenderer::clearMessage()
{
    currentMessage.clear();
}