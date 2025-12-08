#pragma once
#include <string>

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

	AllyParameter();

	AllyParameter
	(std::string n, int h, int m,
		int atk, int def, int spd,
		int lvl, int exp);
};