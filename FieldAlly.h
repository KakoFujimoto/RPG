#pragma once
#include"ICharacter.h"
#include"Position.h"
#include"AllyParameter.h"

class FieldAlly : public ICharacter{
private:
	AllyParameter parameter;
	Position pos;
public:
	FieldAlly(std::string name);

	AllyParameter& getParameter();
	std::string getName() { return parameter.name; }

	std::pair<int, int> getPosition() const;
	void setPosition(int x, int y);
	void move();
};