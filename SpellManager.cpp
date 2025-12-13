#include"SpellManager.h"

void SpellManager::addSpell(const Spell& spell)
{
	spells.push_back(spell);
}

std::vector<const Spell*> SpellManager::getLearnedSpells() const
{
	std::vector<const Spell*> learned;

	for (auto& spell : spells)
	{
		if (spell.getIsLearned())
		{
			learned.push_back(&spell);
		}
	}
	return learned;
}