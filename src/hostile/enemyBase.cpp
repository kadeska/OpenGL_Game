#include "enemyBase.hpp"

#include "../misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;
// log("-- Constructor", LogLevel::DEBUG);

EnemyBase::EnemyBase()
{
	log("EnemyBase Constructor", LogLevel::DEBUG);
}

void EnemyBase::init(int _level, float _health, float _baseDamage, float _damageModifire, float _agression)
{
	log("EnemyBase init", LogLevel::DEBUG);
	_enemyData = {_level, _health, _baseDamage, _damageModifire, _agression, nullptr};
}

EnemyStruct EnemyBase::getEnemyData()
{
	return _enemyData;
}

void EnemyBase::setTarget(BaseEntity* _target)
{
	_enemyData.target = _target;
}

void EnemyBase::pathfind()
{
	log("Pathfind....");

	float distance = glm::distance(this->getEntityPosition(), _enemyData.target->getEntityPosition());


}

void EnemyBase::move()
{
	log("Move");
}
