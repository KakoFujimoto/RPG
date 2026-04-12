#pragma once
#include"AllyParameter.h"
#include"Position.h"
#include"Item.h"

struct EffectResult;
class Input;

class FieldAlly
{

private:
	Position pos;
	AllyParameter parameter;

	static constexpr int MOVE_SPEED = 5;

	void addPositionX(int x);
	void addPositionY(int y);

public:
	FieldAlly();
	FieldAlly(const Position pos, AllyParameter parameter);
	void move(const Input& input);
	AllyParameter& getParameter();
	std::string getName();
	int getX();
	int getY();
	const Position& getPosition() const { return pos; }
	EffectResult useItem(const Item& item);
	EffectResult castSpell(const Spell& spell);
};