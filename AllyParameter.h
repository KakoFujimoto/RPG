#pragma once
#include <string>
#include"SpellManager.h"

class AllyParameter {
public:
	std::string name;
	int maxHp;
	int maxMp;
	int hp;
	int mp;
	int attackPower;
	int defensePower;
	int speed;
	int level;
	int gainedExp;
	SpellManager spellManager;

	struct AllyStatusView {
		std::string name;
		int hp;
		int maxHp;
		int mp;
		int maxMp;
		int level;
	};

	AllyParameter();

	AllyParameter
	(std::string n, int maxHp, int maxMp,
		int atk, int def, int spd,
		int lvl, int exp);

	SpellManager& getSpellManager();
	const SpellManager& getSpellManager() const;
	AllyStatusView getStatusView() const;
};