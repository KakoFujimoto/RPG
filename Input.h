#pragma once
#include "GameKey.h"



class Input {
public:
	void update();
	bool isPressed(GameKey key) const;
	bool isTriggered(GameKey key) const;
};
