#pragma once
#include <string>
#include"SpellManager.h"

class AllyParameter {
public:
	std::string name;
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
		int mp;
		int level;
	};

	AllyParameter();

	AllyParameter
	(std::string n, int h, int m,
		int atk, int def, int spd,
		int lvl, int exp);

	SpellManager& getSpellManager();
	const SpellManager& getSpellManager() const;
	AllyStatusView getStatusView() const;
};