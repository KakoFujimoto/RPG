#include"IdleStatusRenderer.h"

IdleStatusRenderer::IdleStatusRenderer(Display& d) : display(d) {}

void IdleStatusRenderer::setTarget(const AllyParameter* p)
{
    target = p;
}

void IdleStatusRenderer::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}

void IdleStatusRenderer::draw()
{
    if (!target) {
        return;
    }

    auto view = target->getStatusView();

    // ---- ウィンドウサイズ ----
    int width = 160;
    int height = 110;

    int borderColor = GetColor(255, 255, 255);
    int fillColor = GetColor(0, 0, 0);
    int textColor = GetColor(255, 255, 255);

    // ---- ウィンドウ描画 ----
    display.drawWindow(
        posX,
        posY,
        width,
        height,
        borderColor,
        fillColor
    );

    // ---- テキスト描画 ----
    int y = posY + 15;

    display.drawText(posX + 10, y, view.name, textColor);
    y += 20;

    display.drawText(
        posX + 10, y,
        "HP: " + std::to_string(view.hp),
        textColor
    );
    y += 20;

    display.drawText(
        posX + 10, y,
        "MP: " + std::to_string(view.mp),
        textColor
    );
    y += 20;

    display.drawText(
        posX + 10, y,
        "Lv: " + std::to_string(view.level),
        textColor
    );
}
