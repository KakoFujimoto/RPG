#include"Display.h"
#include<DxLib.h>

void Display::showMenu(const std::vector<std::string>& items, int startX, int startY) {
	const int itemHeight = 30; // 各メニュー項目の高さ
	const int textColor = GetColor(255, 255, 255); // 白色
	for (size_t i = 0; i < items.size(); ++i) {
		DrawString(startX, startY + static_cast<int>(i) * itemHeight, items[i].c_str(), textColor);
	}
}