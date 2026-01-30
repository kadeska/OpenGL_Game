#include <string>

#include "gameObject.hpp"
#include "../misc/programLogger.hpp"
#include "collisionTests.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;

//GameObject::GameObject(glm::vec3 _position, float _radius)
//{
//	position = _position;
//	radius = _radius;
//
//	collisionSphere._center = _position;
//	collisionSphere._radius = _radius;
//}

//AABB* goAABB = new AABB{ {0,0,0},{0,0,0} };
//Sphere* goSphere = new Sphere{ {0,0,0}, 0 };




GameObject::GameObject(GO_Type _type, glm::vec3 _position, Renderable::Renderable* _renderable)
{
	log("Constructing GameObject of type: " + std::to_string(static_cast<int>(_type)) + 
		", at pos: " + 
		" X=" + std::to_string(_position.x) + 
		" Y=" + std::to_string(_position.y) + 
		" Z=" + std::to_string(_position.z), LogLevel::DEBUG_V);

	// set the type of game object
	type = _type;

	// null check for renderable. We can have a game object that does not have a renderable object, 
	// such as invisible walls or event triggers.
	if (_renderable != nullptr) 
	{
		// set that game objects renderable object
		gameObjectRenderable = _renderable;
	} else
	{
		log("GameObject: _renderable is nullptr. This game Object should be a event trigger or invisable wall or other non renderable object.", LogLevel::DEBUG_V);
		// do something, or dont return.
		//return;
	}

	// construct the physics object based off of the game object type

	constructPhysicsObject(_type);

	// set the game objects position
	setPosition(_position);


	//if (!physicsObject)
	//{
	//	//physicsObject = new PhysicsObject;
	//	constructPhysicsObject(Physics_Type::PT_NULL);
	//}


	

	// set game objects position 
	//setPosition(_position);

	// figure out what type of collission object to use based off of go_type
	// do type spacific stuff

	

	//switch (_type)
	//{
	//case GO_Type::T_NULL:
	//	log("WARNING: GO type given is null. Did you mean to do this?", LogLevel::DEBUG_V);
	//	//return;
	//	break;
	//case GO_Type::PLAYER:
	//	log("Setting up SPLAYER collision sphere", LogLevel::DEBUG_V);
	//	initAABB();
	//	// lastly set its position
	//	setPosition(_position);
	//	break;
	//case GO_Type::HOSTILE:
	//	log("Setting up HOSTILE collision sphere", LogLevel::DEBUG_V);
	//	initAABB();
	//	// lastly set its position
	//	setPosition(_position);
	//	break;
	//case GO_Type::GROUND:
	//	initAABB();
	//	// lastly set its position
	//	setPosition(_position);
	//	break;
	//case GO_Type::WALL:
	//	log("Setting up WALL aabb", LogLevel::DEBUG_V);
	//	initAABB();
	//	// lastly set its position
	//	setPosition(_position);
	//	break;
	//case GO_Type::ITEM:
	//	log("Setting up ITEM collition sphere", LogLevel::DEBUG_V);
	//	//aabb = new AABB(glm::vec3(0,0,0), glm::vec3(3,3,3)); // set the bounding box 
	//	initAABB();
	//	// lastly set its position
	//	setPosition(_position);
	//	break;
	//default:
	//	break;
	//}

	
}

void GameObject::initAABB()
{
	log("Setting up aabb", LogLevel::DEBUG_V);
	// go through the list of meshes and for each mesh, 
	// go through its list of vertices and find the Max and Min values
	for (int mesh_index = 0; mesh_index < gameObjectRenderable->model->meshes.size(); mesh_index++)
	{
		// do something for the mesh at mesh_index
		for (int vert_index = 0; vert_index < gameObjectRenderable->model->meshes[mesh_index].vertices.size(); vert_index++)
		{
			// for every vertex in this mesh

			// set current pos of the vertex we are testing
			currentVertPos = gameObjectRenderable->model->meshes[mesh_index].vertices[vert_index].Position;

			// max test ---

			// if this vertex is greater than the previus vertex, then set max pos to current pos
			if ((currentVertPos.y > prevVertPos.y) ||
				(currentVertPos.x > prevVertPos.x) ||
				(currentVertPos.z > prevVertPos.z))
			{
				// this vertex is higher up than the previos vert posision.
				// so set the maxPos to the current pos
				maxVertPos = currentVertPos;
				// set previus to current
				prevVertPos = currentVertPos;
				// move onto min test
			}

			// min test ---

			// if this vertex is less then prev then set min
			if ((currentVertPos.y < prevVertPos.y) ||
				(currentVertPos.x < prevVertPos.x) ||
				(currentVertPos.z < prevVertPos.z))
			{
				minVertPos = currentVertPos;
				prevVertPos = currentVertPos;
			}

			// end of tests ---
		}
	}



	// set bounding box min and max posisions.
	if (!physicsObject->aabb)
	{
		// set aabb if its nullptr
		physicsObject->aabb = new AABB();
	}

	log("bounding box Min X: " + std::to_string(minVertPos.x) +
		" , Y: " + std::to_string(minVertPos.y) +
		" , Z: " + std::to_string(minVertPos.z),
		LogLevel::DEBUG_V);

	// set the bounding box min pos
	physicsObject->aabb->_min = minVertPos;

	log("bounding box Max X: " + std::to_string(maxVertPos.x) +
		" , Y: " + std::to_string(maxVertPos.y) +
		" , Z: " + std::to_string(maxVertPos.z),
		LogLevel::DEBUG_V);

	// set bounding box max pos
	physicsObject->aabb->_max = maxVertPos;

	setAABB(physicsObject->aabb);
}

void GameObject::initCollisionSphere()
{
	physicsObject->collisionSphere = new Sphere();
	//physicsObject->collisionSphere->_center = { 0,0,0 };
}


PhysicsObject* GameObject::getPhysicsObject()
{
	return physicsObject;
}

void GameObject::constructPhysicsObject(GO_Type _type)
{
	// initialize physics object
	
	physicsObject = new PhysicsObject();

	// set physics object type based off of game object type

	switch (_type)
	{
	case GO_Type::T_NULL:
		log("GO_Type is null. Setting physics object type to NULL", LogLevel::WARNING);
		physicsObject->physicsType = Physics_Type::PT_NULL;
		break;
	case GO_Type::PLAYER:
		log("GO_Type is PLAYER. Setting physics object type to AABB", LogLevel::DEBUG_V);
		physicsObject->physicsType = Physics_Type::AABB;
		break;
	case GO_Type::HOSTILE:
		log("GO_Type is HOSTILE. Setting physics object type to AABB", LogLevel::DEBUG_V);
		physicsObject->physicsType = Physics_Type::AABB;
		break;
	case GO_Type::FRIENDLY:
		log("GO_Type is FRIENDLY. Setting physics object type to AABB", LogLevel::DEBUG_V);
		physicsObject->physicsType = Physics_Type::AABB;
		break;
	case GO_Type::GROUND:
		log("GO_Type is GROUND. Setting physics object type to AABB", LogLevel::DEBUG_V);
		physicsObject->physicsType = Physics_Type::AABB;
		break;
	case GO_Type::WALL:
		log("GO_Type is WALL. Setting physics object type to AABB", LogLevel::DEBUG_V);
		physicsObject->physicsType = Physics_Type::AABB;
		break;
	case GO_Type::ITEM:
		log("GO_Type is ITEM. Setting physics object type to SPHERE", LogLevel::DEBUG_V);
		physicsObject->physicsType = Physics_Type::SPHERE;
		break;
	default:
		break;
	}

	// set up the actual physics object based off of its type

	switch (physicsObject->physicsType)
	{
	
	case Physics_Type::AABB:
		log("Physics_Type is AABB. Initializing AABB.", LogLevel::DEBUG_V);
		initAABB();
		break;
	case Physics_Type::SPHERE:
		log("Physics_Type is SPHERE. Initializing collision sphere.", LogLevel::DEBUG_V);
		initCollisionSphere();
		break;
	case Physics_Type::PT_NULL:
		log("Physics_Type is NULL. No physics object will be created.", LogLevel::WARNING);
		break;
	default:
		log("Physics_Type is unknown. No physics object will be created.", LogLevel::ERROR);
		break;
	}
}

Sphere* GameObject::getCollisionSphere()
{
	if (physicsObject->collisionSphere == nullptr)
	{
		 log("model collision sphere is null", LogLevel::ERROR);
		return nullptr;
	}
	return physicsObject->collisionSphere;
}

glm::vec3 GameObject::getPosition() // this function gets called every frame??? Maybe fix this
{
	if (physicsObject->collisionSphere) 
	{
		return physicsObject->collisionSphere->_center;
	}
	if (physicsObject->aabb) 
	{
		//return aabb->_center;
		//return {0,0,0};
		//
		return physicsObject->aabb->_centerPosition;
	}
	log("Position is not set", LogLevel::WARNING);
	return {0,0,0};
}

void GameObject::setPosition(glm::vec3 _position)
{
	switch (physicsObject->physicsType)
	{
	case Physics_Type::AABB:
		log("Setting position of AABB physics object to: X= " + std::to_string(_position.x) + 
			", Y= " + std::to_string(_position.y) + 
			", Z= " + std::to_string(_position.z), LogLevel::DEBUG_V);

		if (!physicsObject->aabb) 
		{
			log("AABB is not initialized! Failing to set position", LogLevel::ERROR);
			return;
		}

		physicsObject->aabb->_centerPosition = {
			(physicsObject->aabb->_max.x / 2) + (physicsObject->aabb->_min.x / 2),
			(physicsObject->aabb->_max.y / 2) + (physicsObject->aabb->_min.y / 2),
			(physicsObject->aabb->_max.z / 2) + (physicsObject->aabb->_min.z / 2) };

		break;
	case Physics_Type::SPHERE:
		log("Setting position of SPHERE physics object to: X= " + std::to_string(_position.x) +
			", Y= " + std::to_string(_position.y) +
			", Z= " + std::to_string(_position.z), LogLevel::DEBUG_V);

		if (!physicsObject->collisionSphere)
		{
			log("SPHERE is not initialized! Failing to set position", LogLevel::ERROR);
			return;
		}

		physicsObject->collisionSphere->_center = _position;
		break;
	default:
		log("Unknown physics type" + static_cast<int>(physicsObject->physicsType), LogLevel::WARNING);
		break;
	}

	return;


	//if (physicsObject->collisionSphere)
	//{
	//	// set collision sphere posisiton
	//	physicsObject->collisionSphere->_center = _position;
	//	return;
	//}
	//if (physicsObject->aabb)
	//{
	//	// set aabb center pos ???


	//	physicsObject->aabb->_centerPosition = {
	//		(physicsObject->aabb->_max.x/2) + (physicsObject->aabb->_min.x/2), 
	//		(physicsObject->aabb->_max.y / 2) + (physicsObject->aabb->_min.y / 2), 
	//		(physicsObject->aabb->_max.z / 2) + (physicsObject->aabb->_min.z / 2) };
	//	glm::vec3 pos = physicsObject->aabb->_centerPosition;
	//	log("AABB center pos: " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z), LogLevel::DEBUG_V);
	//	return;
	//}
	//log("Physics object is invalid!!!", LogLevel::ERROR);
}
