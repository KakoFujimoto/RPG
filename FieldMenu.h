#pragma once
#include<string>
#include<vector>
#include"Display.h"
#include"GameManager.h"
#include"Item.h"
#include"MenuItem.h"
#include"StatusWindowRenderer.h"
#include"AllyParameter.h"
#include"SpellWindowRenderer.h"
#include"ItemWindowRenderer.h"
#include"IdleStatusRenderer.h"
#include"EffectWindowRenderer.h"
#include"ItemBag.h"
#include"EffectResult.h"
#include "FieldMenuDrawer.h"

// 責務が多すぎる/責務外の処理もあると認識しています。

class Input;

class FieldMenu {
private:
	std::vector<MenuItem> menuItems{
		{ "ITEM", "どうぐ" },
		{ "STATUS", "つよさ" },
		{ "SPELL", "じゅもん" },
		{ "BACK", "もどる" }
	};
	// フラグ類はよくないと認識しています。
	bool isOpen = false;
	bool isItemListOpen = false;
	bool isParameterOpen = false;
	bool isSpellListOpen = false;
	bool escPushed = false;
	int selectedIndex = 0;
	int idleFrameCount = 0;
	bool isIdleStatusVisible = false;
	bool prevEnterMain = false;
	bool prevEnterItem = false;
	bool prevEnterSpell = false;
	bool prevBattleUp = false;
	bool prevBattleDown = false;
	bool prevUp = false;
	bool prevDown = false;
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
<<<<<<< HEAD
	// ���O���킩��Â炢
	bool isBattleWaitingMessageAck = false;
=======
	bool justEnteredEnemyTurn = false;
>>>>>>> canBattleStartStateDisplay
	GameManager* gm;
	Display display;
	StatusWindowRenderer statusRenderer;
	SpellWindowRenderer spellRenderer;
	AllyParameter& allyParameter;
	ItemWindowRenderer itemRenderer;
	IdleStatusRenderer idleRenderer;
	EffectWindowRenderer effectRenderer;
	ItemBag* itemBag;
	EffectResult lastEffect;
	FieldMenuDrawer menuDrawer;

public:
	FieldMenu(GameManager* gm, Display& display, AllyParameter& allyParameter);
	void choose();
	void select(bool enterPressed);
	void open();
	void close();
	void update(const Input& input);
	void draw(Display& display);
	bool getIsOpen () const;
	bool isSubWindowOpen();
	void showEffect(const EffectResult& result);
	void updateBattleMenu();
	void resetBattleUi();
	void updateBattleItem();
	void updateBattleSpell(const Input& input);
};
