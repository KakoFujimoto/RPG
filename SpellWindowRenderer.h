#pragma once
#include "Display.h"
#include"AllyParameter.h"

class AllyParameter;
class Display;
class SpellWindowRenderer {
private:
    Display& display;
    const AllyParameter* target = nullptr;
    int posX = 0;
    int posY = 0;
    int selectedIndex = 0;
    bool prevUp = false;
    bool prevDown = false;

public:
    SpellWindowRenderer(Display& d);
    void setTarget(AllyParameter* p);
    void setPosition(int x, int y);
    void draw();
    void update();
    const Spell* getSelectedSpells() const;
};
