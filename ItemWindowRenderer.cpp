#include"ItemWindowRenderer.h"
#include<DxLib.h>

ItemWindowRenderer::ItemWindowRenderer(Display& d) : display(d) {}

void ItemWindowRenderer::setTarget(const ItemBag* bag)
{
	itemBag = bag;
    selectedIndex = 0;
}

void ItemWindowRenderer::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}

void ItemWindowRenderer::draw()
{
    if (!itemBag) return;

    const auto& items = itemBag->getItems();

    int visibleCount = 0;
    for (const auto& item : items) {
        if (item.getAmount() > 0) {
            visibleCount++;
        }
    }
    int width = 220;
    int height = 40 + visibleCount * 20;

    display.drawWindow(
        posX, posY,
        width, height,
        GetColor(255, 255, 255),
        GetColor(0, 0, 0)
    );

    int y = posY + 20;
    int textColor = GetColor(255, 255, 255);
    int cursorColor = GetColor(255, 255, 255);

    int drawIndex = 0;

    for (const auto& item : items)
    {
        if (item.getAmount() <= 0) {
            continue;
        }

        if (drawIndex == selectedIndex) {
            display.drawCursor(posX + 5, y, cursorColor);
        }

        std::string text =
            item.getName() + " " + std::to_string(item.getAmount());

        display.drawText(posX + 20, y, text, textColor);

        y += 20;
        drawIndex++;
    }
}


bool ItemWindowRenderer::isCloseRequested() const
{
    return CheckHitKey(KEY_INPUT_ESCAPE);
}

void ItemWindowRenderer::update()
{
    if (!itemBag) return;

    int visibleCount = 0;
    for (const auto& item : itemBag->getItems()) {
        if (item.getAmount() > 0) {
            visibleCount++;
        }
    }

    if (visibleCount == 0) return;

    bool up = CheckHitKey(KEY_INPUT_UP);
    bool down = CheckHitKey(KEY_INPUT_DOWN);

    if (up && !prevUp) {
        selectedIndex = (selectedIndex - 1 + visibleCount) % visibleCount;
    }

    if (down && !prevDown) {
        selectedIndex = (selectedIndex + 1) % visibleCount;
    }

    prevUp = up;
    prevDown = down;
}
