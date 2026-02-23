#pragma once
#include<string>
#include<vector>

class Display {
public:
	//void showMenu(const std::vector<std::string>& items, int startX, int startY);
	void drawWindow(int x, int y, int width, int height, int borderColor, int fillColor);
	void drawText(int x, int y, const std::string& text, int color);
	void drawCursor(int x, int y, int color);
};