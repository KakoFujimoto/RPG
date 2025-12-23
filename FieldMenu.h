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

class FieldMenu {
private:
	std::vector<MenuItem> menuItems{
		{ "ITEM", "‚Ç‚¤‚®" },
		{ "STATUS", "‚Â‚æ‚³" },
		{ "SPELL", "‚¶‚ã‚à‚ñ" },
		{ "BACK", "‚à‚Ç‚é" }
	};

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
	bool prevBattleEnter = false;
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

public:
	FieldMenu(GameManager* gm, Display& display, AllyParameter& allyParameter);
	void choose();
	void select(bool enterPressed);
	void open();
	void close();
	void update();
	void draw(Display& display);
	bool getIsOpen () const;
	bool isSubWindowOpen();
	void showEffect(const EffectResult& result);
	void updateBattleMenu();
	void resetBattleUi();
};
