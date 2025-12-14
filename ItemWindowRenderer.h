#pragma once
#include<DxLib.h>
#include "Display.h"
#include"ItemBag.h"

class ItemWindowRenderer {
private:
    Display& display;
    const ItemBag* itemBag = nullptr;
    int posX = 0;
    int posY = 0;
public:
    ItemWindowRenderer(Display& d);
    void setTarget(const ItemBag* bag);
    void setPosition(int x, int y);
    void draw();
    bool isCloseRequested() const;
};
