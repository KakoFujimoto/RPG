#include"SpellManager.h"
#include"EffectResult.h"
#include"FieldAlly.h"

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

EffectResult SpellManager::castSpell(
    const std::string& spellName,
    FieldAlly& ally
)
{
    auto it = std::find_if(
        spells.begin(),
        spells.end(),
        [&](const Spell& s) {
            return s.getName() == spellName;
        }
    );

    EffectResult result;
    result.success = false;

    if (it == spells.end()) {
        return result;
    }

    return ally.castSpell(*it);
}
