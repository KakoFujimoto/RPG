#pragma once
#include<string>

class ICharacter {
public:
	virtual std::string getName() = 0;
	//virtual void takeDamage() = 0;
	//virtual void isDead() = 0;
	//virtual void move() = 0;
};