#pragma once
#include"Input.h"
#include"SpellWindowRenderer.h"
#include"ItemBag.h"
#include"ItemWindowRenderer.h"
#include"EffectResult.h"
#include"BattleMenuState.h"

class GameManager;
class Display;
class BattleManager;

class BattleMenu
{
private:
    int battleMenuIndex = 0;

    GameManager* gm;
    BattleManager* bm;
    SpellWindowRenderer spellRenderer;
    AllyParameter& allyParameter;
    ItemBag* itemBag;
    ItemWindowRenderer itemRenderer;
    EffectResult lastEffect;
    BattleMenuState state = BattleMenuState::CommandSelect;
    BattleMenuState prevState; // 前フレームの状態を表す

public:
    BattleMenu(
        GameManager* gm,
        BattleManager* bm,
        Display& display,
        AllyParameter& allyParameter,
        ItemBag* itemBag);
    void update(const Input& input);
    void draw();

private:
    void updateBattleMenu(const Input& input);
    void updateBattleItem(const Input& input);
    void updateBattleSpell(const Input& input);
    void resetBattleUi();
};