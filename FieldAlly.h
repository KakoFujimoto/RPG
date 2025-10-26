#pragma once
#include"ICharacter.h"
#include"AllyParameter.h"
#include"Position.h"

class FieldAlly : public ICharacter
{

private:
	Position pos;
	AllyParameter parameter;

	void addPositionX(int x);
	void addPositionY(int y);

public:
	FieldAlly(std::string name, int x, int y);
	void move();
	AllyParameter& getParameter();
	std::string getName();
	std::pair<int, int> getPosition();

};