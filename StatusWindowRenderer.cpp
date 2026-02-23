#include"StatusWindowRenderer.h"
#include<DxLib.h>

StatusWindowRenderer::StatusWindowRenderer(Display& d) : display(d) {}

void StatusWindowRenderer::draw()
{
    if (!target) {
        return;
    }

    int col = GetColor(255, 255, 255);
    const int lineHeight = 20;

    // 表示行数をモードで決定

    int lineCount = 0;

    // 共通(戦闘・フィールド共通)
    lineCount += 4;

    if (mode == StatusViewMode::FieldParameter) {

        lineCount += 4;
    }

    int windowWidth = 260;
    int windowHeight = 20 + lineCount * lineHeight + 10;

    display.drawWindow(
        posX, posY,
        windowWidth, windowHeight,
        GetColor(255, 255, 255),
        GetColor(0, 0, 0)
    );

    int y = posY + 20;


    display.drawText(posX + 10, y,
        "なまえ: " + target->name, col);
    y += lineHeight;

    display.drawText(posX + 10, y,
        "HP: " + std::to_string(target->hp) +
        " / " + std::to_string(target->maxHp), col);
    y += lineHeight;

    display.drawText(posX + 10, y,
        "MP: " + std::to_string(target->mp) +
        " / " + std::to_string(target->maxMp), col);
    y += lineHeight;

    display.drawText(posX + 10, y,
        "Lv: " + std::to_string(target->level), col);
    y += lineHeight;

    if (mode == StatusViewMode::FieldParameter) {

        display.drawText(posX + 10, y,
            "こうげき力: " + std::to_string(target->attackPower), col);
        y += lineHeight;

        display.drawText(posX + 10, y,
            "ぼうぎょ力: " + std::to_string(target->defensePower), col);
        y += lineHeight;

        display.drawText(posX + 10, y,
            "すばやさ: " + std::to_string(target->speed), col);
        y += lineHeight;

        display.drawText(posX + 10, y,
            "けいけんち: " + std::to_string(target->gainedExp), col);
    }
}


void StatusWindowRenderer::setTarget(const AllyParameter* p)
{
	target = p;
}
void StatusWindowRenderer::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}

// ここもSpellWindowRendererと同じく修正可能
bool StatusWindowRenderer::isCloseRequested() const
{
	return CheckHitKey(KEY_INPUT_ESCAPE);
}
void StatusWindowRenderer::setMode(StatusViewMode m)
{ 
    mode = m;
}