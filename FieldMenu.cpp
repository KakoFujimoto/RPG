#include"FieldMenu.h"
#include"DxLib.h"

FieldMenu::FieldMenu(GameManager* gm)
	: gm(gm){ }

void FieldMenu::select()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		std::string id = menuItems[selectedIndex].id;

		if (id == "BACK") {
			isOpen = false;
		}
		else if (id == "ITEM") {
			isItemListOpen = true;
		}
		else if (id == "STATUS") {
			isParameterOpen = true;
		}
		else if (id == "SPELL") {
			isSpellListOpen = true;
		}
	}
}

void FieldMenu::open()
{
	isOpen = true;
	selectedIndex = 0;
	isItemListOpen = 0;
	isSpellListOpen = 0;
	isParameterOpen = 0;
}

void FieldMenu::close()
{
	isOpen = true;
	selectedIndex = 0;
	isItemListOpen = 0;
	isSpellListOpen = 0;
	isParameterOpen = 0;
}

void FieldMenu::update()
{
	// SPACEキーで開く
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (!isOpen) {
			open();
		}
	}

	// ESCキーで閉じる
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		if (isOpen) {
			close();
		}
	}

	if (isOpen) {
		choose();
		select();
	}
}
void FieldMenu::draw(Display& display)
{
	if (!isOpen) return; // 開いていなければ何もしない

	int x = 100, y = 100;
	int width = 200, height = 150;
	int borderColor = GetColor(255, 255, 255);
	int fillColor = GetColor(0, 0, 80);

	display.drawWindow(x, y, width, height, borderColor, fillColor);

	int textColor = GetColor(255, 255, 255);
	int cursorColor = GetColor(255, 255, 255);
	int lineHeight = 30;

	for (int i = 0; i < static_cast<int>(menuItems.size()); ++i) {
		int itemY = y + 20 + i * lineHeight;

		if (i == selectedIndex) {
			display.drawCursor(x + 5, itemY, cursorColor);
		}

		display.drawText(x + 25, itemY, menuItems[i].label, textColor);
	}

	if (isItemListOpen) {
		drawItemList();
	}
	else if (isSpellListOpen) {
		drawSpellList();
	}
	else if (isParameterOpen) {
		drawParameter();
	}
}


bool FieldMenu::getIsOpen() const {
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
void FieldMenu::drawItemList()
{
	// 半透明ウィンドウを重ねる（背景を薄くして区別）
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(220, 60, 400, 220, GetColor(0, 0, 80), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	std::vector<Item>& items = gm->getItemBag().getItems();

	int y = 85;
	for (const auto& item : items)
	{
		std::string text = item.getName() + " " + std::to_string(item.getAmount());
		DrawString(240, y, text.c_str(), GetColor(255, 255, 255));
		y += 20;
	}

	DrawString(240, 180, "Escape:閉じる", GetColor(180, 180, 180));

}
void FieldMenu::drawParameter()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(220, 60, 400, 220, GetColor(0, 0, 80), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 仮のパラメータ
	std::vector<std::string> itemList = {
		"ちから 9",
		"みのまもり 13",
		"すばやさ 17"
	};

	for (int i = 0; i < itemList.size(); i++)
	{
		DrawString(240, 85 + i * 20, itemList[i].c_str(), GetColor(255, 255, 255));
	}

	DrawString(240, 180, "Escape:閉じる", GetColor(180, 180, 180));

}
void FieldMenu::drawSpellList()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(220, 60, 400, 220, GetColor(0, 0, 80), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 仮の呪文リスト
	std::vector<std::string> itemList = {
		"ホイミ",
		"ベホイミ"
	};
	for (int i = 0; i < itemList.size(); i++)
	{
		DrawString(240, 85 + i * 20, itemList[i].c_str(), GetColor(255, 255, 255));
	}

	DrawString(240, 180, "Escape:閉じる", GetColor(180, 180, 180));

}
