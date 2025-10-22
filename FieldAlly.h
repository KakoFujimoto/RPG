#pragma once
#include"ICharacter.h"
#include"AllyParameter.h"
#include"Positionable.h"

class FieldAlly : public ICharacter,
	public Positionable{

private:
	AllyParameter parameter;

public:
	FieldAlly(std::string name);
	void move();
	AllyParameter& getParameter();
	std::string getName();
};