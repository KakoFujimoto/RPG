#pragma once

class IBuff {
public:
	virtual ~IBuff() = default;

	// ƒpƒ‰ƒ[ƒ^‚ğ‘‰Á‚³‚¹‚é
	virtual void increase() = 0;
};