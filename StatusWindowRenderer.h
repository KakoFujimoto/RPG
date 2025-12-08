#pragma once
#include<DxLib.h>
#include "Display.h"
#include"AllyParameter.h"

// ‚Ì‚¿‚Ù‚ÇÀ‘•ƒtƒ@ƒCƒ‹‚É•ª‚¯‚é
class AllyParameter;
class Display;
class StatusWindowRenderer {
private:
    Display& display;

public:
    StatusWindowRenderer(Display& d) : display(d) {}

    void show(const AllyParameter& p, int x, int y) {
        display.drawWindow(x, y, 250, 150, GetColor(255, 255, 255), GetColor(0, 0, 0));

        int col = GetColor(255, 255, 255);
        display.drawText(x + 10, y + 20, "Name: " + p.name, col);
        display.drawText(x + 10, y + 40, "HP: " + std::to_string(p.hp), col);
        display.drawText(x + 10, y + 60, "MP: " + std::to_string(p.mp), col);
        // ‘±‚«‚Í‚Ü‚¾‚ ‚é ¦‘‚¯‚Ä‚È‚¢
    }
};
