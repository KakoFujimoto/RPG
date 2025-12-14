#pragma once
#include<DxLib.h>
#include "Display.h"
#include"AllyParameter.h"

class AllyParameter;
class Display;
class StatusWindowRenderer {
private:
    Display& display;
    const AllyParameter* target = nullptr;
    int posX = 0;
    int posY = 0;
public:
    StatusWindowRenderer(Display& d);
    void setTarget(const AllyParameter* p);
    void setPosition(int x, int y);
    void draw();
    bool isCloseRequested() const;
};
