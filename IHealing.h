#pragma once

class IHealing {
public:
	virtual ~IHealing() = default;

	// hp�Amp���񕜂�����
	virtual void recover(Player& target) = 0;
};