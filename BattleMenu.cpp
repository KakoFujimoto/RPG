#include "BattleMenu.h"
#include "GameManager.h"
#include <DxLib.h>
#include"BattleMessageBuilder.h"

BattleMenu::BattleMenu(
	GameManager* gm,
	Display& display,
	AllyParameter& allyParameter,
	ItemBag* itemBag)
	: gm(gm)
	, spellRenderer(display)
	, allyParameter(allyParameter)
	, itemBag(itemBag)
	, itemRenderer(display)
{
}

void BattleMenu::update(const Input& input)
{
	bool nowBattle = gm->isBattle();

	// 戦闘突入検知
	if (nowBattle && !prevIsBattle)
	{
		resetBattleUi();
		justEnteredBattle = true;
	}
	prevIsBattle = nowBattle;

	if (!nowBattle)
	{
		return;
	}

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

	// 戦闘開始直後1フレーム待ち
	if (justEnteredBattle)
	{
		justEnteredBattle = false;
		return;
	}

	// 逃走タイマー
	if (isBattleRunningAway)
	{
		if (GetNowCount() - battleRunStartTime > 1200)
		{
			gm->endBattle();
			isBattleRunningAway = false;
		}
		return;
	}

	// どうぐ最優先
	if (isBattleItemListOpen)
	{
		updateBattleItem(input);
		return;
	}

	// じゅもん最優先
	if (isBattleSpellListOpen)
	{
		updateBattleSpell(input);
		return;
	}

	// 敵ターン処理
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

			Command dummy(Command::Type::Attack);
			gm->getBattleManager().executeRound(dummy);

			prevBattleEnterMenu = true;
			return;
		}

		prevBattleEnterMenu = enter;
		return;
	}

	// 通常戦闘メニュー
	updateBattleMenu(input);

	// Esc終了
	bool esc = CheckHitKey(KEY_INPUT_ESCAPE) != 0;
	if (esc && !prevBattleEsc)
	{
		gm->endBattle();
	}
	prevBattleEsc = esc;
}

void BattleMenu::updateBattleMenu(const Input& input)
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
	prevBattleEnterMenu = enter;
}

void BattleMenu::updateBattleItem(const Input& input)
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

void BattleMenu::updateBattleSpell(const Input& input)
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
	{
		prevBattleEsc = true;
		isBattleSpellListOpen = false;
		prevBattleEnterSpell = true;
		prevBattleEnterMenu = true;
		return;
	}

	prevBattleEnterSpell = enter;
}

void BattleMenu::resetBattleUi()
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

void BattleMenu::draw()
{
	auto& battleRenderer = gm->getBattleWindowRenderer();

	battleRenderer.setBattleInfo(&gm->getBattleInfo());
	battleRenderer.setAllyParameter(&allyParameter);
	battleRenderer.draw();

	if (isBattleItemListOpen)
	{
		itemRenderer.draw();
	}

	if (isBattleSpellListOpen)
	{
		spellRenderer.draw();
	}
}