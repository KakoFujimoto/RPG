#include"Display.h"
#include<DxLib.h>

//void Display::showMenu(const std::vector<std::string>& items, int startX, int startY) {
//	const int itemHeight = 30; // 各メニュー項目の高さ
//	const int textColor = GetColor(255, 255, 255); // 白色
//	for (size_t i = 0; i < items.size(); ++i) {
//		DrawString(startX, startY + static_cast<int>(i) * itemHeight, items[i].c_str(), textColor);
//	}
//}

void Display::drawWindow(int x, int y, int width, int height, int borderColor, int fillColor) {
	DrawBox(x, y, x + width, y + height, fillColor, TRUE); // 塗りつぶし
	DrawBox(x, y, x + width, y + height, borderColor, FALSE); // 枠線
}

void Display::drawText(int x, int y, const std::string& text, int color) {
	DrawString(x, y, text.c_str(), color);
}

void Display::drawCursor(int x, int y, int color) {
	DrawString(x, y, ">", color);
}