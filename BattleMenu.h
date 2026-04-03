#pragma once
#include "Input.h"
#include"SpellWindowRenderer.h"
#include"ItemBag.h"
#include"ItemWindowRenderer.h"
#include"EffectResult.h"
#include"BattleMenuState.h"

class GameManager;
class Display;

class BattleMenu
{
private:
    bool prevBattleUp = false;
    bool prevBattleDown = false;
    int battleMenuIndex = 0;
    bool prevBattleEsc = false;
    bool prevBattleEnterMenu = false;
    bool prevBattleEnterItem = false;
    bool prevBattleEnterSpell = false;
    bool prevIsBattle = false;
    bool justEnteredBattle = false;


    // == リファクタ対象 ==
    bool justEnteredEnemyTurn = false;
    // == リファクタ対象ここまで ==


	GameManager* gm;
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
