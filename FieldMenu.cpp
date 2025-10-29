#include"FieldMenu.h"
#include"DxLib.h"

void FieldMenu::choose()
{	
	if (!isOpen)
	{
		return;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		selectedIndex--;
		if (selectedIndex < 0)
		{
			selectedIndex = menuItems.size() - 1;
		}
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		selectedIndex++;
		if (selectedIndex >= menuItems.size())
		{
			selectedIndex = 0;
		}
	}
}

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
    int lineHeight = 30;
    for (int i = 0; i < 4; ++i) {
        display.drawText(x + 20, y + 20 + i * lineHeight, menuItems[i], textColor);
    }
}

bool FieldMenu::getIsOpen() const
{
	return isOpen;
}
