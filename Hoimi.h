#pragma once
#include"Name.h"
#include"RecoverSpell.h"
#include"RandomGenerator.h"

class Player;
class Hoimi : public RecoverSpell {
public:
	Hoimi(RandomGenerator& rng) : RecoverSpell(rng,"ƒzƒCƒ~", 3) {};
};