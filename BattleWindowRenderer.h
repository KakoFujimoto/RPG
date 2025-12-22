#pragma once
#include "Display.h"
#include "StatusWindowRenderer.h"

struct BattleStartInfo;
class BattleWindowRenderer {
private:
    Display& display;
    int x = 50;
    int y = 50;
    int width = 700;
    int height = 500;
    const BattleStartInfo* battleInfo = nullptr;
    void drawEnemyInfo();
    void drawMessage();
    void drawMonster();
    void drawAllyStatus();
    const AllyParameter* allyParam = nullptr;
    StatusWindowRenderer allyStatusRenderer;

public:
    BattleWindowRenderer(Display& d);
    void setPosition(int px, int py);
    void setSize(int w, int h);
    void draw();
    void setBattleInfo(const BattleStartInfo* info);
    void setAllyParameter(const AllyParameter* ally);
};
