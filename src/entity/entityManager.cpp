#include <glm/fwd.hpp>

#include "entityManager.hpp"

#include "../misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;

EntityManager::EntityManager(World* _world)
{
	for (GameObject* go : _world->getGameObjects()) 
	{
		switch (go->getType())
		{
		case GO_Type::ITEM:
			addEntityItem(new Entity_Item {go, go->getPosition(), 0, 1});
			break;
		case GO_Type::HOSTILE:
			addEntityEnemy(new Entity_Enemy {go, go->getPosition(), 0, 0, 0});
			break;
		case GO_Type::FRIENDLY:
			addEntityFriendly(new Entity_Friendly {go, go->getPosition(), 0, 0});
			break;
		case GO_Type::PLAYER:
			break;
		default:
			break;
		}
	}
}

void EntityManager::addEntityItem(Entity_Item* _item)
{
	//check for null
	if (!_item) 
	{
		log("From addEntityItem(): Entity_Item is null", LogLevel::ERROR);
		return;
	}
	itemArray.push_back(_item);
}

void EntityManager::addEntityEnemy(Entity_Enemy* _enemy)
{
	//check for null
	if (!_enemy)
	{
		log("From addEntityItem(): Entity_Enemy is null", LogLevel::ERROR);
		return;
	}
	enemyArray.push_back(_enemy);
}

void EntityManager::addEntityFriendly(Entity_Friendly* _friendly)
{
	//check for null
	if (!_friendly)
	{
		log("From addEntityItem(): Entity_Friendly is null", LogLevel::ERROR);
		return;
	}
	friendlyArray.push_back(_friendly);
}
