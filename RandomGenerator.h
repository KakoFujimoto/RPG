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

	// 座標用ランダム生成（例: 0～maxX-1 / 0～maxY-1）
	std::pair<int, int> getRandomPosition(int maxX, int maxY) {
		std::uniform_int_distribution<> distX(0, maxX - 1);
		std::uniform_int_distribution<> distY(0, maxY - 1);
		return { distX(gen), distY(gen) };
	}
};