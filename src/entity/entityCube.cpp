#include "EntityCube.hpp"



EntityCube::EntityCube()
{
	log("EntityCube Constructor1", LogLevel::DEBUG);
	// I dont need to do this as the BaseEntity constructor already does it.
	// 
	//this->setEntityID(-1);
	//this->setEntityPosition(glm::vec3(0,0,0));
	//this->setEntityName("NULL");
}

EntityCube::EntityCube(int _id, glm::vec3 _loc)
{
	log("EntityCube Constructor2", LogLevel::DEBUG);
	this->setEntityID(_id);
	this->setEntityPosition(_loc);
	this->setEntityName("Block");
	//isInteractable = false;
}

EntityCube::~EntityCube()
{
}

void EntityCube::setIsInteractable(bool _isInteractable)
{
	isInteractable = _isInteractable;
}

bool EntityCube::getIsInteractable()
{
	return isInteractable;
}