#pragma once
#include "Display.h"
#include"AllyParameter.h"

class AllyParameter;
class Display;

enum class StatusViewMode {
    FieldParameter,
    BattleParameter
};

class StatusWindowRenderer {
private:
    Display& display;
    const AllyParameter* target = nullptr;
    int posX = 0;
    int posY = 0;
    StatusViewMode mode = StatusViewMode::FieldParameter;
public:
    StatusWindowRenderer(Display& d);
    void setTarget(const AllyParameter* p);
    void setPosition(int x, int y);
    void draw();
    // Ç±Ç±Ç‡SpellWindowRendererÇ∆ìØÇ∂Ç≠èCê≥â¬î\
    bool isCloseRequested() const;
    void setMode(StatusViewMode m);
};
