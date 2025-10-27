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

public:
	void open(Display& display);
	void choose();
	void select();
	void close();
};