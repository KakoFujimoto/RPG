#include"SpellManager.h"

void SpellManager::learnSpell(const Spell& spell)
{	
	Spell obj = spell;
	obj.learn();
	spells.push_back(obj);
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