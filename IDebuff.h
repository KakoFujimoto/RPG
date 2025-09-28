#pragma once

class IDebuff {
public:
	virtual ~IDebuff() = default;

	// ƒpƒ‰ƒ[ƒ^‚ğ‘‰Á‚³‚¹‚é
	virtual void decrease() = 0;
};