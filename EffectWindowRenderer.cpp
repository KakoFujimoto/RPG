#include"EffectWindowRenderer.h"
#include"EffectResult.h"
#include"Display.h"
#include<string>
#include<DxLib.h>

EffectWindowRenderer::EffectWindowRenderer(Display& d) : display(d) {}

void EffectWindowRenderer::draw()
{
    if (!visible || !result || !result->success) {
        return;
    }

    int borderColor = GetColor(255, 255, 255);
    int fillColor = GetColor(0, 0, 0);

    display.drawWindow(posX, posY, width, height, borderColor, fillColor);

    int textColor = GetColor(255, 255, 255);

    int textX = posX + 20;
    int textY = posY + 20;

    // 1行目
    display.drawText(
        textX,
        textY,
        result->userName + "は" + result->itemName + "をつかった！",
        textColor
    );

    // 2行目
    if (result->hpDelta > 0) {
        display.drawText(
            textX,
            textY + 30,
            result->userName + "のHPが" +
            std::to_string(result->hpDelta) + "かいふくした！",
            textColor
        );
    }
    else if (result->mpDelta > 0) {
        display.drawText(
            textX,
            textY + 30,
            result->userName + "のMPが" +
            std::to_string(result->mpDelta) + "かいふくした！",
            textColor
        );
    }
    showFrame++;
    if (showFrame >= 120) { // 約2秒
        hide();
    }
}

void EffectWindowRenderer::setResult(const EffectResult* r)
{
    result = r;
}

void EffectWindowRenderer::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}
void EffectWindowRenderer::show()
{
    visible = true;
    showFrame = 0;
}

void EffectWindowRenderer::hide()
{
    visible = false;
    showFrame = 0;
}