#pragma once
#include"Name.h"
#include"Spell.h"
#include"RandomGgenerator.h"

class Player;
class Hoimi : public Spell {
public:
	Hoimi() : Spell("ƒzƒCƒ~", 3, 25) {};
	void recover(Player& target) override;

};