#pragma once
#include"Name.h"
#include"IHealing.h"

class Player;
class Hoimi : public IHealing {
private:
	Name name;

public:
	void recover(Player& target) override;

};