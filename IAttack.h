#pragma once

class IAttack {
public:
	virtual ~IAttack() = default;

	// �_���[�W��^����
	virtual void damege() = 0;
};
