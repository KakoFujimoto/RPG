#include"FieldMenu.h"
#include"DxLib.h"
#include"EffectResult.h"
#include"BattleMessageBuilder.h"
#include"BattleWindowRenderer.h"
#include"BattleDamageCalculator.h"
#include"Command.h"
#include"Input.h"
#include<Windows.h>

namespace FieldMenuConst
{
	// UI位置
	constexpr int MENU_X = 100;
	constexpr int MENU_Y = 100;
	constexpr int MENU_WIDTH = 200;
	constexpr int MENU_HEIGHT = 150;

	constexpr int SUB_WINDOW_X = 200;
	constexpr int SUB_WINDOW_Y = 120;

	constexpr int IDLE_X = 520;
	constexpr int IDLE_Y = 420;

	constexpr int EFFECT_X = 50;
	constexpr int EFFECT_Y = 300;

	// ロジック
	constexpr int IDLE_FRAME_THRESHOLD = 120;
}

FieldMenu::FieldMenu(GameManager* gm, Display& display, AllyParameter& allyParameter)
	: gm(gm),
	display(display),
	statusRenderer(display),
	spellRenderer(display),
	allyParameter(allyParameter),
	itemRenderer(display),
	idleRenderer(display),
	effectRenderer(display),
	itemBag(&gm->getItemBag())
{
	idleRenderer.setTarget(&allyParameter);
	idleRenderer.setPosition(
		FieldMenuConst::IDLE_X,
		FieldMenuConst::IDLE_Y
	);
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
		itemRenderer.setPosition(
			FieldMenuConst::SUB_WINDOW_X,
			FieldMenuConst::SUB_WINDOW_Y);
		prevEnterItem = CheckHitKey(KEY_INPUT_RETURN);
		return;
	}
	else if (id == "STATUS") {
		isParameterOpen = true;
		statusRenderer.setTarget(&allyParameter);
		statusRenderer.setPosition(
			FieldMenuConst::SUB_WINDOW_X,
			FieldMenuConst::SUB_WINDOW_Y);
		return;
	}
	else if (id == "SPELL") {
		isSpellListOpen = true;
		spellRenderer.setTarget(&allyParameter);
		spellRenderer.setPosition(
			FieldMenuConst::SUB_WINDOW_X,
			FieldMenuConst::SUB_WINDOW_Y);
		prevEnterSpell = CheckHitKey(KEY_INPUT_RETURN);
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

void FieldMenu::update(const Input& input)
{
	// アイドル判定（ここは冗長なため暫定）
	bool idle =
		!input.isPressed(GameKey::Up) &&
		!input.isPressed(GameKey::Down) &&
		!input.isPressed(GameKey::Left) &&
		!input.isPressed(GameKey::Right) &&
		!input.isPressed(GameKey::Decide) &&
		!input.isPressed(GameKey::Cancel);

	if (idle)
	{
		idleFrameCount++;
		if (idleFrameCount >= FieldMenuConst::IDLE_FRAME_THRESHOLD)
		{
			isIdleStatusVisible = true;
		}
	}
	else
	{
		idleFrameCount = 0;
		isIdleStatusVisible = false;
	}

	// メニュー未オープン
	if (!isOpen)
	{
		if (input.isTriggered(GameKey::Decide))
		{
			open();
		}
		return;
	}

	// アイテム
	if (isItemListOpen)
	{
		itemRenderer.update();

		if (input.isTriggered(GameKey::Decide))
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
			return;
		}

		return;
	}

	// ステータス
	if (isParameterOpen)
	{
		if (statusRenderer.isCloseRequested())
		{
			isParameterOpen = false;
		}
		return;
	}

	// じゅもん
	if (isSpellListOpen)
	{
		spellRenderer.update();

		if (input.isTriggered(GameKey::Decide))
		{
			const Spell* spell = spellRenderer.getSelectedSpells();
			if (spell)
			{
				EffectResult r =
					allyParameter.getSpellManager()
					.castSpell(spell->getName(), gm->getAlly());
				showEffect(r);
			}
		}

		if (input.isTriggered(GameKey::Cancel))
		{
			isSpellListOpen = false;
			return;
		}

		return;
	}

	// メインメニュー

	if (input.isTriggered(GameKey::Cancel))
	{
		close();
		return;
	}

	// カーソル移動
	if (input.isTriggered(GameKey::Up))
	{
		selectedIndex--;
		if (selectedIndex < 0)
		{
			selectedIndex = static_cast<int>(menuItems.size()) - 1;
		}
	}

	if (input.isTriggered(GameKey::Down))
	{
		selectedIndex++;
		if (selectedIndex >= static_cast<int>(menuItems.size()))
		{
			selectedIndex = 0;
		}
	}

	// 決定
	if (input.isTriggered(GameKey::Decide))
	{
		select(true);
	}
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

	int borderColor = GetColor(255, 255, 255);
	int fillColor = GetColor(0, 0, 0);

	display.drawWindow(
		FieldMenuConst::MENU_X,
		FieldMenuConst::MENU_Y,
		FieldMenuConst::MENU_WIDTH,
		FieldMenuConst::MENU_HEIGHT,
		borderColor,
		fillColor
	);

	std::vector<std::string> labels;
	labels.reserve(menuItems.size());
	for (const auto& item : menuItems)
	{
		labels.push_back(item.label);
	}

	menuDrawer.draw(
		display,
		labels,
		selectedIndex,
		FieldMenuConst::MENU_X,
		FieldMenuConst::MENU_Y
	);


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
void FieldMenu::choose()
{
	if (!isOpen) return;
	if (isSubWindowOpen()) return;

	bool currentUp = CheckHitKey(KEY_INPUT_UP);
	bool currentDown = CheckHitKey(KEY_INPUT_DOWN);

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
	effectRenderer.setPosition(
		FieldMenuConst::EFFECT_X,
		FieldMenuConst::EFFECT_Y
	);
	effectRenderer.show();
}