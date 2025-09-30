#pragma once
#include<random>

class RandomGenerator {
private:
	std::mt19937 gen;

public:
	RandomGenerator() : gen(std::random_device{}()){}

	// �����p�Ƀ����_���l��Ԃ�(��b�l�𒆐S�ɁAmin�`max�̃����_���l��Ԃ�)
	int getRandomValue(int min, int max) {
		std::uniform_int_distribution<> dist(min, max);
		return dist(gen);
	}

	// ��p�Ƀ����_���l��Ԃ�(��b�l�ƕ����w�肷��/25�}5��)
	int getRandomincreasedPoint(int base, int rdm) {
		std::uniform_int_distribution<> dist(base - rdm, base - rdm);
		return dist(gen);
	}
};