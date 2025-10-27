#include"FieldMenu.h"
#include"DxLib.h"

//void FieldMenu::open(Display& display)
//{
//	if (CheckHitKey(KEY_INPUT_SPACE))
//	{
//		isOpen = true;
//	}
//	if (isOpen)
//	{
//		display.showMenu(menuItems, 50, 50);
//	}
//}

void FieldMenu::close()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		isOpen = false;
	}
}

void FieldMenu::update(Display& display)
{
    // SPACEキーで開く
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        isOpen = true;
    }

    // ESCキーで閉じる
    if (CheckHitKey(KEY_INPUT_ESCAPE)) {
        isOpen = false;
    }

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
