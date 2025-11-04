#pragma once
#include<string>
#include<vector>
#include"Display.h"
#include"GameManager.h"
#include"Item.h"


class FieldMenu {
private:
	std::vector<std::string> menuItems{
	"‚Ç‚¤‚®",
	"‚Â‚æ‚³",
	"‚¶‚ã‚à‚ñ",
	"‚à‚Ç‚é"
	};

	bool isOpen = false;
	bool isItemListOpen = false;
	bool isParameterOpen = false;
	bool isSpellListOpen = false;
	int selectedIndex = 0;
	GameManager* gm;

public:
	FieldMenu(GameManager* gm);
	void choose();
	void select();
	void open();
	void close();
	void update();
	void draw(Display& display);
	bool getIsOpen () const;
	void drawItemList();
	void drawParameter();
	void drawSpellList();

};
