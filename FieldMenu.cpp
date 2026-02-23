#include"FieldMenu.h"
#include"DxLib.h"
#include"EffectResult.h"
#include"BattleMessageBuilder.h"
#include"BattleWindowRenderer.h"
#include"BattleDamageCalculator.h"
#include"Command.h"
#include"Input.h"
#include<Windows.h>

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

// 繰り返し表現が多く、よくないと認識している
// 詰め込みすぎとも。
void FieldMenu::update(const Input& input)
{	
	// 戦闘中のロジックがここにあるのもおかしい気はしている
	// 戦闘中の入力（ここで完結）
	bool nowBattle = (gm && gm->isBattle());

	if (nowBattle && !prevIsBattle)
	{
		resetBattleUi();
		justEnteredBattle = true;
	}
	prevIsBattle = nowBattle;

	if (nowBattle)
	{	
		// デバッグ用
		{
			std::string dbg =
				"[DEBUG] BattleInputState\n"
				"  isEnemyTurn=" + std::to_string(gm->getBattleManager().isEnemyTurn()) + "\n" +
				"  prevBattleEnterMenu=" + std::to_string(prevBattleEnterMenu) + "\n" +
				"  enter=" + std::to_string(CheckHitKey(KEY_INPUT_RETURN) != 0) + "\n";

			OutputDebugStringA(dbg.c_str());
		}

		bool enterNow = CheckHitKey(KEY_INPUT_RETURN) != 0;
		if (!enterNow)
		{
			prevBattleEnterMenu = false;
		}

		if (justEnteredBattle)
		{
			justEnteredBattle = false;
			return;
		}

		if (isBattleRunningAway)
		{
			if (GetNowCount() - battleRunStartTime > 1200)
			{
				gm->endBattle();
				resetBattleUi();
				isBattleRunningAway = false;
			}
			return;
		}
		// 戦闘中はアイドル表示を止める
		idleFrameCount = 0;
		isIdleStatusVisible = false;

		// ① 最前面：どうぐ
		if (isBattleItemListOpen)
		{
			updateBattleItem();
			return;
		}

		// ② 最前面：じゅもん
		if (isBattleSpellListOpen)
		{
			updateBattleSpell(input);
			return;
		}
		if (gm->getBattleManager().isEnemyTurn())
		{
			if (justEnteredEnemyTurn)
			{
				bool enterNow = CheckHitKey(KEY_INPUT_RETURN) != 0;
				if (!enterNow)
				{
					justEnteredEnemyTurn = false;
				}
				return;
			}

			bool enter = CheckHitKey(KEY_INPUT_RETURN);
			bool enterPressed = enter && !prevBattleEnterMenu;

			if (enterPressed)
			{
				prevBattleEnterMenu = enter;

				// EnemyTurnではCommandの中身は使われない
				Command dummy(Command::Type::Attack);
				gm->getBattleManager().executeRound(dummy);

				prevBattleEnterMenu = true;
				return;
			}

			prevBattleEnterMenu = enter;
			return;
		}

		// ③ 戦闘メニュー
		updateBattleMenu();

		// ④ Esc で戦闘終了
		bool esc = CheckHitKey(KEY_INPUT_ESCAPE) != 0;
		if (esc && !prevBattleEsc)
		{
			gm->endBattle();
			resetBattleUi();
		}
		prevBattleEsc = esc;

		return;
	}


	// ここから下はフィールド専用

	prevBattleEsc = false;

	bool idle = !CheckHitKeyAll();
	if (idle)
	{
		idleFrameCount++;
		if (idleFrameCount >= 120)
		{
			isIdleStatusVisible = true;
		}
	}
	else
	{
		idleFrameCount = 0;
		isIdleStatusVisible = false;
	}

	int esc = CheckHitKey(KEY_INPUT_ESCAPE);

	if (!esc)
	{
		escPushed = false;
	}

	bool enter = CheckHitKey(KEY_INPUT_RETURN);

	if (!isOpen)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			open();
			prevEnterMain = enter;
			prevEnterItem = enter;
		}
		return;
	}

	// サブウィンドウ類
	// アイテム
	if (isItemListOpen)
	{
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

		// ここもSpellWindowRendererと同じく修正可能
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

	// ステータス
	if (isParameterOpen)
	{
		// ここもSpellWindowRendererと同じく修正可能
		if (statusRenderer.isCloseRequested())
		{
			isParameterOpen = false;
			escPushed = true;
		}
		return;
	}

	// じゅもん
	if (isSpellListOpen)
	{
		bool enterPressedSpell = enter && !prevEnterSpell;
		spellRenderer.update();

		if (enterPressedSpell)
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

		if (input.isPressed(GameKey::Cancel))
		{
			isSpellListOpen = false;
			escPushed = true;
			prevEnterSpell = enter;
			return;
		}

		prevEnterSpell = enter;
		return;
	}

	// メインメニュー

	if (!escPushed && esc)
	{
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
	// 設計上問題があるように思うが、完成させることを重視
	if (gm && gm->isBattle())
	{
		auto& battleRenderer = gm->getBattleWindowRenderer();
		battleRenderer.setBattleInfo(&gm->getBattleInfo());
		battleRenderer.setAllyParameter(&gm->getAlly().getParameter());
		battleRenderer.draw();

		if (isBattleItemListOpen)
		{
			itemRenderer.draw();
		}
		if (isBattleSpellListOpen)
		{
			spellRenderer.draw();
		}
		return;
	}
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

	std::vector<std::string> labels;
	labels.reserve(menuItems.size());
	for (const auto& item : menuItems)
	{
		labels.push_back(item.label);
	}

	menuDrawer.draw(display, labels, selectedIndex, x, y);


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
	effectRenderer.setPosition(50, 300);
	effectRenderer.show();
}

void FieldMenu::resetBattleUi()
{
	isBattleItemListOpen = false;
	isBattleSpellListOpen = false;

	// 戦闘コマンドカーソル初期化
	battleMenuIndex = 0;

	// 戦闘コマンドのカーソル位置が戻らない問題対策：押しっぱなしを「既に押されている」として処理する =====
	prevBattleUp = (CheckHitKey(KEY_INPUT_UP) != 0);
	prevBattleDown = (CheckHitKey(KEY_INPUT_DOWN) != 0);
	prevBattleEnterMenu = (CheckHitKey(KEY_INPUT_RETURN) != 0);

	// サブ側もついでにリセット
	prevBattleEnterItem = (CheckHitKey(KEY_INPUT_RETURN) != 0);
	prevBattleEnterSpell = (CheckHitKey(KEY_INPUT_RETURN) != 0);

	prevBattleEsc = (CheckHitKey(KEY_INPUT_ESCAPE) != 0);
}
void FieldMenu::updateBattleItem()
{
	// まずEscを最優先で処理
	// ここもSpellWindowRendererと同じく修正可能
	if (itemRenderer.isCloseRequested())
	{
		isBattleItemListOpen = false;

		// Escをここで消費する
		prevBattleEsc = true;
		prevBattleEnterItem = true;
		return;
	}

	bool enter = CheckHitKey(KEY_INPUT_RETURN) != 0;
	bool enterPressed = enter && !prevBattleEnterItem;

	itemRenderer.update();

	if (enterPressed)
	{
		const Item* item = itemRenderer.getSelectedItem();
		if (item)
		{
			EffectResult result =
				itemBag->useItem(item->getName(), gm->getAlly());

			std::string msg = BattleMessageBuilder::build(result);
			gm->getBattleWindowRenderer().setMessage(msg);

			Command cmd(Command::Type::Item);
			//gm->getBattleManager().executeRound(cmd);

			gm->getBattleManager().notifyAllyActionFinished();
			justEnteredEnemyTurn = true;

			itemRenderer.clampSelectedIndex();
			isBattleItemListOpen = false;

			// 入力消費
			prevBattleEnterItem = true;
			prevBattleEsc = true;
			return;
		}
	}

	prevBattleEnterItem = enter;
}

void FieldMenu::updateBattleSpell(const Input& input)
{
	bool enter = CheckHitKey(KEY_INPUT_RETURN) != 0;
	bool enterPressed = enter && !prevBattleEnterSpell;

	spellRenderer.update();

	if (enterPressed)
	{
		const Spell* spell = spellRenderer.getSelectedSpells();
		if (spell)
		{
			Command cmd;
			cmd.type = Command::Type::Spell;
			cmd.spellName = spell->getName();

			gm->getBattleManager().executeRound(cmd);

			isBattleSpellListOpen = false;
			prevBattleEnterSpell = true;
			prevBattleEnterMenu = true;

			return;
		}
	}

	if (input.isPressed(GameKey::Cancel))
	// if(input.isPressed(GameKey::Cancel) && spellRenderer.canClose())
	{
		isBattleSpellListOpen = false;
		prevBattleEnterSpell = true;
		prevBattleEnterMenu = true;
		return;
	}

	prevBattleEnterSpell = enter;
}


// BattleMenuをUpdateする処理がこのクラスにあるのはおかしいと自覚しています
void FieldMenu::updateBattleMenu()
{
	bool up = CheckHitKey(KEY_INPUT_UP);
	bool down = CheckHitKey(KEY_INPUT_DOWN);
	bool enter = CheckHitKey(KEY_INPUT_RETURN);
	bool enterPressed = enter && !prevBattleEnterMenu;

	int menuCount = gm->getBattleMenuCount();
	if (menuCount <= 0)
	{
		return;
	}

	if (up && !prevBattleUp)
	{
		battleMenuIndex = (battleMenuIndex + menuCount - 1) % menuCount;
	}

	if (down && !prevBattleDown)
	{
		battleMenuIndex = (battleMenuIndex + 1) % menuCount;
	}

	gm->getBattleWindowRenderer()
		.setSelectedMenuIndex(battleMenuIndex);

	if (enterPressed)
	{
		// たたかう
		// とりあえずメッセージ表示だけ（ダメージ量計算は別途）
		if (battleMenuIndex == 0)
		{
			Command cmd(Command::Type::Attack);
			gm->getBattleManager().executeRound(cmd);

			prevBattleEnterMenu = enter;
			return;
		}


		// じゅもん
		if (battleMenuIndex == 1)
		{
			isBattleSpellListOpen = true;
			spellRenderer.setTarget(&allyParameter);
			gm->getBattleWindowRenderer()
				.prepareSpellWindow(spellRenderer);

			prevBattleEnterSpell = true;
			return;
		}

		// ぼうぎょ
		if (battleMenuIndex == 2)
		{
			Command cmd(Command::Type::Guard);

			gm->getBattleManager().executeRound(cmd);

			prevBattleEnterMenu = true;
			return;
		}

		// どうぐ
		if (battleMenuIndex == 3)
		{
			isBattleItemListOpen = true;
			itemRenderer.setTarget(itemBag);
			gm->getBattleWindowRenderer()
				.prepareItemWindow(itemRenderer);

			prevBattleEnterItem = true;
			return;
		}

		// にげる
		if (battleMenuIndex == 4)
		{
			std::string msg =
				gm->getAlly().getName() + "は にげだした!";
			gm->getBattleWindowRenderer().setMessage(msg);

			isBattleRunningAway = true;
			battleRunStartTime = GetNowCount();

			return;
		}
	}

	prevBattleUp = up;
	prevBattleDown = down;
}