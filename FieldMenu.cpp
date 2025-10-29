#include"FieldMenu.h"
#include"DxLib.h"

//void FieldMenu::choose()
//{	
//	if (!isOpen)
//	{
//		return;
//	}
//	if (CheckHitKey(KEY_INPUT_UP))
//	{
//		selectedIndex--;
//		if (selectedIndex < 0)
//		{
//			selectedIndex = menuItems.size() - 1;
//		}
//	}
//	else if (CheckHitKey(KEY_INPUT_DOWN))
//	{
//		selectedIndex++;
//		if (selectedIndex >= menuItems.size())
//		{
//			selectedIndex = 0;
//		}
//	}
//}

void FieldMenu::select()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		// 選択されたメニュー項目に応じた処理をここに追加
		std::string selectedItem = menuItems[selectedIndex];
		if (selectedItem == "もどる")
		{
			isOpen = false;
		}
		// 他のメニュー項目の処理もここに追加可能
	}
}

void FieldMenu::close()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		isOpen = false;
	}
}

void FieldMenu::update()
{
	// SPACEキーで開く
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		isOpen = true;
	}

	// ESCキーで閉じる
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		isOpen = false;
	}

	if (isOpen) {
		choose();
		select();
	}
}

void FieldMenu::draw(Display & display)
{
	if (!isOpen) return; // 開いていなければ何もしない
	
	// ===== メニュー描画部分 =====
    int x = 100, y = 100;
    int width = 200, height = 150;
    int borderColor = GetColor(255, 255, 255);
    int fillColor = GetColor(0, 0, 80);

    display.drawWindow(x, y, width, height, borderColor, fillColor);

    // メニュー項目を縦に描画
    int textColor = GetColor(255, 255, 255);
	int cursorColor = GetColor(255, 255, 255);
    int lineHeight = 30;

    for (int i = 0; i < static_cast<int>(menuItems.size()); ++i) {
		int itemY = y + 20 + i * lineHeight;

		if (i == selectedIndex) {
			display.drawCursor(x + 5, itemY, cursorColor);
		}
        display.drawText(x + 25, itemY, menuItems[i], textColor);
    }
}

bool FieldMenu::getIsOpen() const
{
	return isOpen;
}

void FieldMenu::choose() {
	if (!isOpen) return;

	static int prevUp = 0;
	static int prevDown = 0;

	int currentUp = CheckHitKey(KEY_INPUT_UP);
	int currentDown = CheckHitKey(KEY_INPUT_DOWN);

	// キーの押下を1回ずつだけ検知
	if (currentUp && !prevUp) {
		selectedIndex--;
		if (selectedIndex < 0) {
			selectedIndex = static_cast<int>(menuItems.size()) - 1;
		}
	}
	if (currentDown && !prevDown) {
		selectedIndex++;
		if (selectedIndex >= static_cast<int>(menuItems.size())) {
			selectedIndex = 0;
		}
	}

	prevUp = currentUp;
	prevDown = currentDown;
}