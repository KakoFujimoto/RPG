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
#include"BattleWindowRenderer.h"

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
	GameManager* gm;
	Display display;
	StatusWindowRenderer statusRenderer;
	SpellWindowRenderer spellRenderer;
	AllyParameter& allyParameter;
	ItemWindowRenderer itemRenderer;
	IdleStatusRenderer idleRenderer;
	EffectWindowRenderer effectRenderer;
	BattleWindowRenderer battleRenderer;
	ItemBag* itemBag;
	bool prevEnterMain = false;
	bool prevEnterItem = false;
	bool prevEnterSpell = false;
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
};
