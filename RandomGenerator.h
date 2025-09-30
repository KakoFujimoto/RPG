#pragma once
#include<random>

class RandomGenerator {
private:
	std::mt19937 gen;

public:
	RandomGenerator() : gen(std::random_device{}()){}

	// 呪文用にランダム値を返す(基礎値を中心に、min～maxのランダム値を返す)
	int getRandomValue(int min, int max) {
		std::uniform_int_distribution<> dist(min, max);
		return dist(gen);
	}

	// 種用にランダム値を返す(基礎値と幅を指定する/25±5等)
	int getRandomincreasedPoint(int base, int rdm) {
		std::uniform_int_distribution<> dist(base - rdm, base - rdm);
		return dist(gen);
	}
};