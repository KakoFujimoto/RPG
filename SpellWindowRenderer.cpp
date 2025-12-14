#include"SpellWindowRenderer.h"

SpellWindowRenderer::SpellWindowRenderer(Display& d) : display(d){ }

void SpellWindowRenderer::setTarget(const AllyParameter* p)
{
	target = p;
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

	int width = 220;
	int height = 40 + spells.size() + 20;

	display.drawWindow(posX, posY, width, height,
		GetColor(255, 255, 255), GetColor(0, 0, 0));

	int textColor = GetColor(255, 255, 255);
	int yOffset = posY + 20;

	for (const Spell* s : spells)
	{
		display.drawText(posX + 20, yOffset, s->getName(), textColor);
		yOffset += 20;
	}
}

bool SpellWindowRenderer::isCloseRequested() const
{
	return CheckHitKey(KEY_INPUT_ESCAPE);
}