#pragma once

class IDebuff {
public:
	virtual ~IDebuff() = default;

	// �p�����[�^�𑝉�������
	virtual void decrease() = 0;
};