#include "BattleMenu.h"
#include "GameManager.h"
#include "BattleManager.h"
#include "BattleMessageBuilder.h"

namespace BattleText
{
	constexpr const char* RunAway = "は にげだした!";
}

BattleMenu::BattleMenu(
	GameManager* gm,
	BattleManager* bm,
	Display& display,
	AllyParameter& allyParameter,
	ItemBag* itemBag)
	: gm(gm)
	, bm(bm)
	, spellRenderer(display)
	, allyParameter(allyParameter)
	, itemBag(itemBag)
	, itemRenderer(display)
{
	resetBattleUi();
}

void BattleMenu::update(const Input& input)
{
	if (bm->consumeSkipInput())
	{
		return;
	}

	if (state == BattleMenuState::ItemSelect)
	{
		updateBattleItem(input);
		return;
	}

	if (state == BattleMenuState::SpellSelect)
	{
		updateBattleSpell(input);
		return;
	}

	if (bm->isRunningAway())
	{
		return;
	}

	if (bm->isEnemyTurn())
	{
		if (input.isTriggered(GameKey::Decide))
		{
			bm->requestEnemyTurnAction();
		}
		return;
	}

	updateBattleMenu(input);

	if (input.isTriggered(GameKey::Cancel))
	{
		gm->endBattle();
	}
}

void BattleMenu::updateBattleMenu(const Input& input)
{
	int menuCount = gm->getBattleMenuCount();
	if (menuCount <= 0)
	{
		return;
	}

	if (input.isTriggered(GameKey::Up))
	{
		battleMenuIndex = (battleMenuIndex + menuCount - 1) % menuCount;
	}

	if (input.isTriggered(GameKey::Down))
	{
		battleMenuIndex = (battleMenuIndex + 1) % menuCount;
	}

	gm->getBattleWindowRenderer().setSelectedMenuIndex(battleMenuIndex);

	if (!input.isTriggered(GameKey::Decide))
	{
		return;
	}

	BattleCommand cmd = static_cast<BattleCommand>(battleMenuIndex);

	switch (cmd)
	{
	case BattleCommand::Attack:
		bm->submitPlayerCommand(Command(Command::Type::Attack));
		break;
	case BattleCommand::Spell:
		state = BattleMenuState::SpellSelect;
		spellRenderer.setTarget(&allyParameter);
		gm->getBattleWindowRenderer().prepareSpellWindow(spellRenderer);
		break;
	case BattleCommand::Guard:
		bm->submitPlayerCommand(Command(Command::Type::Guard));
		break;
	case BattleCommand::Item:
		state = BattleMenuState::ItemSelect;
		itemRenderer.setTarget(itemBag);
		gm->getBattleWindowRenderer().prepareItemWindow(itemRenderer);
		break;
	case BattleCommand::Escape:
		std::string msg =
		gm->getAlly().getName() + BattleText::RunAway;
		gm->getBattleWindowRenderer().setMessage(msg);
		bm->startRunAway();
		break;
	}
}

void BattleMenu::updateBattleItem(const Input& input)
{
	if (itemRenderer.isCloseRequested())
	{
		state = BattleMenuState::CommandSelect;
		return;
	}

	itemRenderer.update();

	if (!input.isTriggered(GameKey::Decide))
	{
		return;
	}

	const Item* item = itemRenderer.getSelectedItem();
	if (!item)
	{
		return;
	}

	EffectResult result =
		itemBag->useItem(item->getName(), gm->getAlly());

	std::string msg = BattleMessageBuilder::build(result);
	gm->getBattleWindowRenderer().setMessage(msg);

	bm->notifyAllyActionFinished();
	itemRenderer.clampSelectedIndex();
	state = BattleMenuState::CommandSelect;
}

void BattleMenu::updateBattleSpell(const Input& input)
{
	spellRenderer.update();

	if (input.isTriggered(GameKey::Decide))
	{
		const Spell* spell = spellRenderer.getSelectedSpells();
		if (spell)
		{
			Command cmd;
			cmd.type = Command::Type::Spell;
			cmd.spellName = spell->getName();

			bm->submitPlayerCommand(cmd);
			state = BattleMenuState::CommandSelect;
			return;
		}
	}

	if (input.isTriggered(GameKey::Cancel))
	{
		state = BattleMenuState::CommandSelect;
	}
}

void BattleMenu::resetBattleUi()
{
	state = BattleMenuState::CommandSelect;
	battleMenuIndex = 0;
}

void BattleMenu::draw()
{
	auto& battleRenderer = gm->getBattleWindowRenderer();

	battleRenderer.setBattleInfo(&gm->getBattleInfo());
	battleRenderer.setAllyParameter(&allyParameter);
	battleRenderer.draw();

	if (state == BattleMenuState::ItemSelect)
	{
		itemRenderer.draw();
	}

	if (state == BattleMenuState::SpellSelect)
	{
		spellRenderer.draw();
	}
}