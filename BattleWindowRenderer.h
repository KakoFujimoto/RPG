#pragma once
#include "Display.h"

class BattleWindowRenderer {
private:
    Display& display;

    int x = 50;
    int y = 50;
    int width = 700;
    int height = 500;

public:
    BattleWindowRenderer(Display& d);

    void setPosition(int px, int py);
    void setSize(int w, int h);

    void draw();
};
