#pragma once
#include<DxLib.h>
#include "Display.h"
#include"AllyParameter.h"

class IdleStatusRenderer {
private:
    Display& display;
    const AllyParameter* target = nullptr;
    int posX = 0;
    int posY = 0;
public:
    IdleStatusRenderer(Display& d);
    void setTarget(const AllyParameter* p);
    void setPosition(int x, int y);
    void draw();
};
