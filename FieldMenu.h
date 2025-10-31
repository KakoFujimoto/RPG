#pragma once
#include<string>
#include<vector>
#include"Display.h"

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

public:
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