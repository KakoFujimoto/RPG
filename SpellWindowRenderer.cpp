#include"SpellWindowRenderer.h"
#include<DxLib.h>

SpellWindowRenderer::SpellWindowRenderer(Display& d) : display(d){ }

void SpellWindowRenderer::setTarget(AllyParameter* p)
{
	target = p;
	selectedIndex = 0;
	prevUp = false;
	prevDown = false;
}

void SpellWindowRenderer::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}

void SpellWindowRenderer::draw()
{
	if (!target)
	{
		return;
	}

	auto& spellManager = target->getSpellManager();
	const std::vector<const Spell*>& spells = spellManager.getLearnedSpells();

	int count = static_cast<int>(spells.size());

	int width = 220;
	int height = 40 + count * 20;


	display.drawWindow(
		posX, posY,
		width, height,
		GetColor(255, 255, 255),
		GetColor(0, 0, 0)
	);

	int textColor = GetColor(255, 255, 255);
	int cursorColor = GetColor(255, 255, 255);
	int yOffset = posY + 20;

	for (int i = 0; i<count; ++i)
	{	
		if (i == selectedIndex)
		{
			display.drawCursor(posX + 5, yOffset, cursorColor);
		}
		display.drawText(
			posX + 20,
			yOffset,
			spells[i]->getName(),
			textColor
		);
		yOffset += 20;
	}
}

bool SpellWindowRenderer::isCloseRequested() const
{
	return CheckHitKey(KEY_INPUT_ESCAPE);
}

void SpellWindowRenderer::update()
{
	if (!target)
	{
		return;
	}

	const auto& spells =
		target->getSpellManager().getLearnedSpells();

	int count = static_cast<int>(spells.size());
	if (count == 0)
	{
		return;
	}

	bool up = CheckHitKey(KEY_INPUT_UP);
	bool down = CheckHitKey(KEY_INPUT_DOWN);

	if (up && !prevUp)
	{
		selectedIndex--;
		if (selectedIndex < 0)
		{
			selectedIndex = count - 1;
		}
	}
	if (down && !prevDown)
	{
		selectedIndex++;
		if (selectedIndex >= count)
		{
			selectedIndex = 0;
		}
	}
	prevUp = up;
	prevDown = down;
}

const Spell* SpellWindowRenderer::getSelectedSpells() const
{
	if (!target)
	{
		return nullptr;
	}
	const auto& spells =
		target->getSpellManager().getLearnedSpells();

	if (spells.empty())
	{
		return nullptr;
	}

	if (selectedIndex < 0 ||
		selectedIndex >= static_cast<int>(spells.size()))
	{
		return nullptr;
	}
	return spells[selectedIndex];
}