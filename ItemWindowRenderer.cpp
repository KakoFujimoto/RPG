#include"ItemWindowRenderer.h"
#include<DxLib.h>

ItemWindowRenderer::ItemWindowRenderer(Display& d) : display(d) {}

void ItemWindowRenderer::setTarget(const ItemBag* bag)
{
	itemBag = bag;
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

    int width = 220;
    int height = 40 + static_cast<int>(items.size()) * 20;

    display.drawWindow(
        posX, posY,
        width, height,
        GetColor(255, 255, 255),
        GetColor(0, 0, 0)
    );

    int y = posY + 20;
    int textColor = GetColor(255, 255, 255);

    for (const auto& item : items)
    {
        std::string text =
            item.getName() + " " + std::to_string(item.getAmount());

        display.drawText(posX + 20, y, text, textColor);
        y += 20;
    }
}

bool ItemWindowRenderer::isCloseRequested() const
{
    return CheckHitKey(KEY_INPUT_ESCAPE);
}
