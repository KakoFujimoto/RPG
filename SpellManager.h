#pragma once
#include<vector>
#include"Spell.h"

class SpellManager {
private:
	std::vector<Spell> spells;

public:
	void addSpell(const Spell& spell);

	std::vector<const Spell*> getLearnedSpells() const;

};
