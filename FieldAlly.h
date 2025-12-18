#pragma once
#include"AllyParameter.h"
#include"Position.h"
#include"Item.h"

class EffectResult;
class FieldAlly
{

private:
	Position pos;
	AllyParameter parameter;

	void addPositionX(int x);
	void addPositionY(int y);

public:
	FieldAlly();
	FieldAlly(const Position pos, AllyParameter parameter);
	void move();
	AllyParameter& getParameter();
	std::string getName();
	int getX();
	int getY();
	const Position& getPosition() const { return pos; }
	EffectResult useItem(const Item& item);
	void castSpell(const Spell& spell);
};