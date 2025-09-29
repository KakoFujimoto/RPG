#pragma once
#include"Name.h"
#include"Spell.h"

class Player;
class Hoimi : public Spell {
public:
	Hoimi() : Spell("ƒzƒCƒ~", 3, 25) {};
	void recover(Player& target) override;

};