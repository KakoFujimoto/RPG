#pragma once
#include <vector>

class FieldEnemy;
class Enemy;
class RandomGenerator;

class FieldEnemyManager {
private:
	std::vector<FieldEnemy> fieldEnemies;
public:
	void spawn(const FieldEnemy& fieldEnemy, int x, int y, RandomGenerator& rng);
	const std::vector<FieldEnemy>& getEnemies() const;
	void draw() const;
};