#include"FieldMenu.h"
#include"DxLib.h"
#include"EffectResult.h"

FieldMenu::FieldMenu(GameManager* gm, Display& display, AllyParameter& allyParameter)
	: gm(gm)
	, display(display)
	, statusRenderer(display)
	, spellRenderer(display)
	, allyParameter(allyParameter)
	, itemRenderer(display)
	, idleRenderer(display)
	, effectRenderer(display)
	, itemBag(&gm->getItemBag())
{
	idleRenderer.setTarget(&allyParameter);
	idleRenderer.setPosition(520, 420);
}

void FieldMenu::select(bool enterPressed)
{
	if (!enterPressed)
	{
		return;
	}
	if (!isOpen)
	{
		return;
	}

	if (isSubWindowOpen())
	{
		return;
	}

	std::string id = menuItems[selectedIndex].id;

	if (id == "BACK") {
		isOpen = false;
	}
	else if (id == "ITEM") {
		isItemListOpen = true;
		itemRenderer.setTarget(itemBag);
		itemRenderer.setPosition(200, 120);

		prevEnterItem = CheckHitKey(KEY_INPUT_RETURN);
		return;
	}
	else if (id == "STATUS") {
		isParameterOpen = true;
		statusRenderer.setTarget(&allyParameter);
		statusRenderer.setPosition(200, 120);
		return;
	}
	else if (id == "SPELL") {
		isSpellListOpen = true;
		spellRenderer.setTarget(&allyParameter);
		spellRenderer.setPosition(200, 120);
		return;
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
	isOpen = false;
	selectedIndex = 0;
	isItemListOpen = 0;
	isSpellListOpen = 0;
	isParameterOpen = 0;
}

void FieldMenu::update()
{	
	bool idle = !CheckHitKeyAll();

	if (idle)
	{
		idleFrameCount++;
		if (idleFrameCount >= 120)
		{
			isIdleStatusVisible = true;
		}
	}
	else {
		idleFrameCount = 0;
		isIdleStatusVisible = false;
	}
	
	int esc = CheckHitKey(KEY_INPUT_ESCAPE);

	if (!esc)
	{
		escPushed = false;
	}

	bool enter = CheckHitKey(KEY_INPUT_RETURN);

	// SPACEキーで開く
	if (!isOpen) {
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			open();
			prevEnterMain = enter;
			prevEnterItem = enter;
		}
		return;
	}
	if (isItemListOpen) {
		bool enterPressedItem = enter && !prevEnterItem;
		itemRenderer.update();

		if (enterPressedItem)
		{
			const Item* item = itemRenderer.getSelectedItem();
			if (item)
			{
				EffectResult r =
					itemBag->useItem(item->getName(), gm->getAlly());
				showEffect(r);
				itemRenderer.clampSelectedIndex();
			}
		}
		if (itemRenderer.isCloseRequested())
		{
			isItemListOpen = false;
			escPushed = true;
			prevEnterMain = enter;
			prevEnterItem = enter;
			return;
		}
		prevEnterItem = enter;
		return;
	}

	if (isParameterOpen) {
		if (statusRenderer.isCloseRequested())
		{
			isParameterOpen = false;
			escPushed = true;
		}
		return;
	}
	if (isSpellListOpen) {
		if (spellRenderer.isCloseRequested())
		{
			isSpellListOpen = false;
			escPushed = true;
		}
		return;
	}
	
	// ESCキーで閉じる
	if (!escPushed && esc) {
		
		close();
		escPushed = true;
		return;
		
	}
	bool enterPressedMain = enter && !prevEnterMain;
	choose();
	select(enterPressedMain);
	prevEnterMain = enter;
}

void FieldMenu::draw(Display& display)
{
	if (isIdleStatusVisible) {
		idleRenderer.draw();
	}

	effectRenderer.draw();

	if (!isOpen) {
		return; // 開いていなければ何もしない
	}

	int x = 100, y = 100;
	int width = 200, height = 150;
	int borderColor = GetColor(255, 255, 255);
	int fillColor = GetColor(0, 0, 0);

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
		itemRenderer.draw();
	}
	else if (isSpellListOpen) {
		spellRenderer.draw();

	}
	else if (isParameterOpen) {
		statusRenderer.draw();
	}
}

bool FieldMenu::getIsOpen() const {
	return isOpen;
}
void FieldMenu::choose() {
	if (!isOpen) {
		return;
	}

	if (isSubWindowOpen()) {
		return;
	}

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

bool FieldMenu::isSubWindowOpen()
{
	return isItemListOpen || isParameterOpen || isSpellListOpen;
}

void FieldMenu::showEffect(const EffectResult& result)
{
	lastEffect = result;
	effectRenderer.setResult(&lastEffect);
	effectRenderer.setPosition(50, 300);
	effectRenderer.show();
}