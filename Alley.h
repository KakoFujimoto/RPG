#pragma once
#include"Name.h"
#include"Position.h"
#include"ICharacter.h"


class FieldAlley : ICharacter{
private:

public:
	std::string getName();
	void takeDamage();
	void isDead();
	void move();
};