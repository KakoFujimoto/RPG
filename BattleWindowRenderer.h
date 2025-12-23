#pragma once
#include "Display.h"
#include "StatusWindowRenderer.h"

struct BattleStartInfo;
class ItemWindowRenderer;
class BattleWindowRenderer {
private:
    Display& display;
    int x = 50;
    int y = 50;
    int width = 700;
    int height = 500;
    int selectedMenuIndex = 0;
    const BattleStartInfo* battleInfo = nullptr;
    int battleStartFrame = -1;
    std::vector<std::string> battleMenuItems{
    "‚½‚½‚©‚¤",
    "‚¶‚ã‚à‚ñ",
    "‚Ú‚¤‚¬‚å",
    "‚Ç‚¤‚®",
    "‚É‚°‚é"
    };
    void drawEnemyInfo();
    void drawMessage();
    void drawMonster();
    void drawAllyStatus();
    void drawMenu();
    const AllyParameter* allyParam = nullptr;
    StatusWindowRenderer allyStatusRenderer;
public:
    BattleWindowRenderer(Display& d);
    void setPosition(int px, int py);
    void setSize(int w, int h);
    void draw();
    void setBattleInfo(const BattleStartInfo* info);
    void setAllyParameter(const AllyParameter* ally);
    void setSelectedMenuIndex(int index);
    int getMenuCount() const;
    void prepareItemWindow(ItemWindowRenderer& itemRenderer);

};
