#include"FieldEnemyManager.h"
#include"FieldEnemy.h"

void FieldEnemyManager::spawn(const FieldEnemy& fieldEnemy, int maxX, int maxY, RandomGenerator& rng)
{
	FieldEnemy fe = fieldEnemy;
	fe.spawn(maxX, maxY, rng);
	fieldEnemies.push_back(fe);
}
const std::vector<FieldEnemy>& FieldEnemyManager::getEnemies() const
{
	return fieldEnemies;
}
void FieldEnemyManager::draw() const
{
	for (const auto& fe : fieldEnemies)
	{
		fe.draw();
	}
}