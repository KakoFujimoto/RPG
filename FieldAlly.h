#pragma once
#include"ICharacter.h"
#include"Position.h"

class Neko;
class FieldAlly {
private:
	ICharacter* character;
	Position pos;
public:
	FieldAlly(ICharacter* c);
	//std::string getName() override;
	//void takeDamage() override;
	//void isDead() override;
	std::pair<int, int> getPosition() const;
	void setPosition(int x, int y);
	void move();
};