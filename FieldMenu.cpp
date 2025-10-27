#include"FieldMenu.h"
#include"DxLib.h"

void FieldMenu::open(Display& display)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		isOpen = true;
	}
	if (isOpen)
	{
		display.showMenu(menuItems, 50, 50);
	}
}

void FieldMenu::close()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		isOpen = false;
	}
}