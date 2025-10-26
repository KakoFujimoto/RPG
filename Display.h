#pragma once
#include<string>
#include<vector>

class Display {
public:
	void showMenu(const std::vector<std::string>& items, int startX, int startY);
};