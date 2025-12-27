#pragma once
#include <string>
#include"SpellManager.h"

class EnemyParameter {
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
	int exp; // “|‚·‚±‚Æ‚Å“¾‚ç‚ê‚éŒoŒ±’l


	EnemyParameter();
	EnemyParameter
	(std::string n, int maxHp, int maxMp,
		int atk, int def, int spd,
		int lvl, int exp);

	const std::string getName() const;
	// ŽÀ‘•‚Í‚Ü‚¾
	void takeDamage(int amount);
	int healHp(int amount);
	int consumeMp(int amount);
	int getHp() const;
	int getMp();
	const int getAttack() const;
	const int getDefense()const;
	int getExp();
};