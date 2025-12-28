#include "enemyNormal.hpp"

EnemyNormal::EnemyNormal(glm::vec3 _location)
{
	log("EntityNormal Constructor", LogLevel::DEBUG);
	setEntityPosition(_location);
}

void EnemyNormal::attack()
{
}
