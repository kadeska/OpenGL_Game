#include "collisionManager.hpp"


bool success = false;

CollisionManager::CollisionManager()
{
}

// need to fix this so it checks what physics object is set and do the right collision checks. 
bool CollisionManager::checkForCollisions(GameObject* _gameObject1, GameObject* _gameObject2)
{
	success = CollisionTests::sphereToPlane(_gameObject1->getCollisionSphere(), glm::vec3(0,1.5,0), glm::vec3(0, 1, 0));
	if (_gameObject2 != nullptr) 
	{
		// collision sphere check first
		if (_gameObject1->getCollisionSphere() && _gameObject2->getCollisionSphere()) 
		{
			return CollisionTests::sphereToSphere(_gameObject1->getCollisionSphere(), _gameObject2->getCollisionSphere());;
		}
		// AABB check next if spere was not available.
		if (_gameObject1->getAABB() && _gameObject2->getAABB()) 
		{
			return CollisionTests::aabbToaabb(_gameObject1->getAABB(), _gameObject2->getAABB());
		}
	}
	


	return success;
}
