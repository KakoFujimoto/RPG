#pragma once
#include"Position.h"
#include"EnemyParameter.h"

class EnemyParameter;
class FieldEnemy {
private:
	Position pos;
	EnemyParameter parameter;
	bool isActive = true;

public:
	FieldEnemy();
	FieldEnemy(const Position pos, EnemyParameter parameter);

	void spawn(int maxX, int maxY, RandomGenerator& rng);
	void draw() const;
	void setEncountered();
	bool getIsActive() const;
	void setIsActive(bool state);
	int getX();
	int getY();
	const Position& getPosition() const;
	const EnemyParameter& getParameter() const;
};