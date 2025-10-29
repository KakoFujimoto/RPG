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
	int selectedIndex = 0;

public:
	void choose();
	void select();
	void close();
	void update();
	void draw(Display& display);
	bool getIsOpen() const;
};