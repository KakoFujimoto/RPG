#include"FieldMenuDrawer.h"
#include"Display.h"
#include<DxLib.h>


void FieldMenuDrawer::draw(
	Display& display,
	const std::vector<std::string>& items,
	int startX,
	int startY
) const
{
	// 本来はマジックナンバーをConfigに切り出せます
	const int itemHeight = 30; // 各メニュー項目の高さ
	const int textColor = GetColor(255, 255, 255); // 白色
	for (size_t i = 0; i < items.size(); ++i) {
		display.drawText(startX, startY + static_cast<int>(i) * itemHeight, items[i], textColor);
	}	
}