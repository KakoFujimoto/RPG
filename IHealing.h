#pragma once

class Player;
class IHealing {
public:
	virtual ~IHealing() = default;

	// hpAmp‚ğ‰ñ•œ‚³‚¹‚é
	virtual void recover(Player& target) = 0;
};