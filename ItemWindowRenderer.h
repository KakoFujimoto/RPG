#pragma once
#include "Display.h"
#include"ItemBag.h"

class ItemWindowRenderer {
private:
    Display& display;
    const ItemBag* itemBag = nullptr;
    int posX = 0;
    int posY = 0;
    int selectedIndex = 0;
    bool prevUp = false;
    bool prevDown = false;

public:
    ItemWindowRenderer(Display& d);
    void setTarget(const ItemBag* bag);
    void setPosition(int x, int y);
    void draw();
    void update();
    bool isCloseRequested() const;
    const Item* getSelectedItem() const;
    int getVisibleCount() const;
    void clampSelectedIndex();
    void resetBattleUi();
};