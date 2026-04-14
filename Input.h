#pragma once
#include "GameKey.h"
#include <array>

class Input {
public:
	void update();
	bool isPressed(GameKey key) const;
	bool isTriggered(GameKey key) const;
	bool isAnyKeyPressed() const;

private:
	static constexpr int KeyCount = 6;
	std::array<bool, KeyCount> currentStates{};
	std::array<bool, KeyCount> previousStates{};

	static int toIndex(GameKey key);
	bool readRaw(GameKey key) const;
};
