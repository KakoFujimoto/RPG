#include"SpellManager.h"

void SpellManager::addSpell(const Spell& spell)
{
	spells.push_back(spell);
}

std::vector<Spell*> SpellManager::getLearnedSpells()
{
	std::vector<Spell*> learned;

	for (auto& spell : spells)
	{
		if (spell.getIsLearned())
		{
			learned.push_back(&spell);
		}
		return learned;
	}
}