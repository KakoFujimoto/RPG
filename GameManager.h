#pragma once
#include"RandomGenerator.h"
#include"Position.h"

class GameManager {
private:
	RandomGenerator rng;
public:
	RandomGenerator getRng() { return rng; }
	bool HitCheck(const Position& allyPosition, const Position& object);
};