#include"FieldMenuDrawer.h"
#include"Display.h"
#include<DxLib.h>


void FieldMenuDrawer::draw(
	Display& display,
	const std::vector<std::string>& labels,
	int selectedIndex,
	int x,
	int y
) const
{
	// 本来はマジックナンバーをConfigに切り出せます
	const int lineHeight = 30; // 各メニュー項目の高さ
	const int textColor = GetColor(255, 255, 255); // 白色
	const int cursorcolor = GetColor(255, 255, 255);


	for (size_t i = 0; i < labels.size(); ++i) {
		int itemY = y + 20 + i * lineHeight;

		if (i == selectedIndex)
		{
			display.drawCursor(x + 5, itemY, cursorcolor);
		}
		display.drawText(
			x + 25,
			itemY,
			labels[i],
			textColor);
	}	
}