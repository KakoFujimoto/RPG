#pragma once
#include"Spell.h"
#include"IHealing.h"

class RecoverSpell : public Spell, public IHealing {
public:
	using Spell::Spell;
};