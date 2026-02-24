#include "BattleMenu.h"
#include "GameManager.h"
#include <DxLib.h>
#include"BattleMessageBuilder.h"


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