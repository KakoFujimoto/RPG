#pragma once

class IBuff {
public:
	virtual ~IBuff() = default;

	// �p�����[�^�𑝉�������
	virtual void increase() = 0;
};