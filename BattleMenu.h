#pragma once
#include "Input.h"
#include"SpellWindowRenderer.h"
#include"ItemBag.h"
#include"ItemWindowRenderer.h"
#include"EffectResult.h"


class GameManager;
class Display;

class BattleMenu
{
private:
	GameManager* gm;

    bool prevBattleUp = false;
    bool prevBattleDown = false;
    int battleMenuIndex = 0;
    bool prevBattleEsc = false;
    bool isBattleItemListOpen = false;
    bool isBattleSpellListOpen = false;
    bool prevBattleEnterMenu = false;
    bool prevBattleEnterItem = false;
    bool prevBattleEnterSpell = false;
    bool prevIsBattle = false;
    bool justEnteredBattle = false;
    bool isBattleRunningAway = false;
    int battleRunStartTime = 0;
    bool justEnteredEnemyTurn = false;

    SpellWindowRenderer spellRenderer;
    AllyParameter& allyParameter;
    ItemBag* itemBag;
    ItemWindowRenderer itemRenderer;
    EffectResult lastEffect;

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
