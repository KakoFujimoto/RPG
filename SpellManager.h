#pragma once
#include<vector>
#include"Spell.h"

struct EffectResult;
class FieldAlly;

class SpellManager {
private:
	std::vector<Spell> spells;

public:
	void learnSpell(const Spell& spell);
	std::vector<const Spell*> getLearnedSpells() const;
	EffectResult castSpell(
		const std::string& spellName,
		FieldAlly& ally
	);
};
