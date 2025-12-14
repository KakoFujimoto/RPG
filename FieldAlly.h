#pragma once
#include"AllyParameter.h"
#include"Position.h"
#include"Item.h"

class FieldAlly
{

private:
	Position pos;
	AllyParameter parameter;

	void addPositionX(int x);
	void addPositionY(int y);

public:
	FieldAlly();
	FieldAlly(std::string name, int x, int y);
	void move();
	AllyParameter& getParameter();
	std::string getName();
	int getX();
	int getY();
	const Position& getPosition() const { return pos; }
	void useItem(Item& item);
	void castSpell(const Spell& spell);
};