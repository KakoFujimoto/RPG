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
#include"FieldMenuDrawer.h"


class Input;

class FieldMenu {
private:
	std::vector<MenuItem> menuItems{
		{ "ITEM", "どうぐ" },
		{ "STATUS", "つよさ" },
		{ "SPELL", "じゅもん" },
		{ "BACK", "もどる" }
	};
	bool isOpen = false;
	bool isItemListOpen = false;
	bool isParameterOpen = false;
	bool isSpellListOpen = false;
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
	ItemBag* itemBag;
	EffectResult lastEffect;
	FieldMenuDrawer menuDrawer;
public:
	FieldMenu(GameManager* gm, Display& display, AllyParameter& allyParameter);
	void choose(const Input& input);
	void select(const Input& input);
	void open();
	void close();
	void update(const Input& input);
	void draw(Display& display);
	bool getIsOpen() const;
	bool isSubWindowOpen();
	void showEffect(const EffectResult& result);
};