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

	//AllyParameter
	//(std::string n, int h, int m,
	//	int atk, int def,int spd,
	//	int lvl, int exp)
	//	: name(n), hp(h), mp(m),
	//	attackPower(atk), defensePower(def), speed(spd),
	//	level(lvl), gainedExp(exp) { }
};