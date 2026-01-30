#include "collisionManager.hpp"


bool success = false;

CollisionManager::CollisionManager()
{
}

// need to fix this so it checks what physics object is set and do the right collision checks. 
bool CollisionManager::checkForCollisions(GameObject* _gameObject1, GameObject* _gameObject2)
{
	// first check if we are testing against anything
	if (_gameObject2 == nullptr) 
	{
		// we now know that we are only testing with one object
		// check what type of physics object it is
		if (_gameObject1->getPhysicsObject()->physicsType == Physics_Type::SPHERE) 
		{
			// if the collision sphere is somehow null, we cant do a test
			if (_gameObject1->getCollisionSphere() == nullptr)
			{
				return false;
			}
			// we will do a plane test for basic ground collision
			return CollisionTests::sphereToPlane(_gameObject1->getCollisionSphere(), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		}
		
		return false;
	}


	// check if the collision objects are the same
	if (_gameObject1->getPhysicsObject()->physicsType == _gameObject2->getPhysicsObject()->physicsType) 
	{
		// we now know the physics objects are the same type, such as both aabb or both sphere
		// make a type variable to make code cleaner
		Physics_Type type = _gameObject1->getPhysicsObject()->physicsType;
		if (type == Physics_Type::AABB) 
		{
			// do AABB test
			return CollisionTests::aabbToaabb(_gameObject1->getAABB(), _gameObject2->getAABB());
		}
		if (type == Physics_Type::SPHERE) 
		{
			// do sphere test
			return CollisionTests::sphereToSphere(_gameObject1->getCollisionSphere(), _gameObject2->getCollisionSphere());
		}
	}

	// type check for aabb or sphere collision



	//success = CollisionTests::sphereToPlane(_gameObject1->getCollisionSphere(), glm::vec3(0,1.5,0), glm::vec3(0, 1, 0));
	//if (_gameObject2 != nullptr) 
	//{
	//	// collision sphere check first
	//	if (_gameObject1->getCollisionSphere() && _gameObject2->getCollisionSphere()) 
	//	{
	//		return CollisionTests::sphereToSphere(_gameObject1->getCollisionSphere(), _gameObject2->getCollisionSphere());;
	//	}
	//	// AABB check next if spere was not available.
	//	if (_gameObject1->getAABB() && _gameObject2->getAABB()) 
	//	{
	//		return CollisionTests::aabbToaabb(_gameObject1->getAABB(), _gameObject2->getAABB());
	//	}
	//}
	


	//return success;

	//log("", logle);
	return false;
}
