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
	// null check for renderable. We can have a game object that does not have a renderable object, 
	// such as invisible walls or event triggers.
	if (_renderable == nullptr)
	{
		log("GameObject: _renderable is nullptr", LogLevel::DEBUG_V);
		// do something, or dont return.
		return;
	}

	if (!physicsObject)
	{
		physicsObject = new PhysicsObject;
	}


	// set that game objects renderable object
	gameObjectRenderable = _renderable;

	// set game objects position 
	//setPosition(_position);

	// figure out what type of collission object to use based off of go_type
	// do type spacific stuff

	

	switch (_type)
	{
	case GO_Type::T_NULL:
		log("WARNING: GO type given is null. Did you mean to do this?", LogLevel::DEBUG_V);
		//return;
		break;
	case GO_Type::PLAYER:
		log("Setting up SPLAYER collision sphere", LogLevel::DEBUG_V);
		initAABB();
		// lastly set its position
		setPosition(_position);
		break;
	case GO_Type::HOSTILE:
		log("Setting up HOSTILE collision sphere", LogLevel::DEBUG_V);
		initAABB();
		// lastly set its position
		setPosition(_position);
		break;
	case GO_Type::GROUND:
		initAABB();
		// lastly set its position
		setPosition(_position);
		break;
	case GO_Type::WALL:
		log("Setting up WALL aabb", LogLevel::DEBUG_V);
		initAABB();
		// lastly set its position
		setPosition(_position);
		break;
	case GO_Type::ITEM:
		log("Setting up ITEM collition sphere", LogLevel::DEBUG_V);
		//aabb = new AABB(glm::vec3(0,0,0), glm::vec3(3,3,3)); // set the bounding box 
		initAABB();
		// lastly set its position
		setPosition(_position);
		break;
	default:
		break;
	}

	type = _type;
}

void GameObject::initAABB()
{
	log("Setting up GROUND aabb", LogLevel::DEBUG_V);
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

	log("bounding box Man X: " + std::to_string(maxVertPos.x) +
		" , Y: " + std::to_string(maxVertPos.y) +
		" , Z: " + std::to_string(maxVertPos.z),
		LogLevel::DEBUG_V);

	// set bounding box max pos
	physicsObject->aabb->_max = maxVertPos;

	setAABB(physicsObject->aabb);
}

void GameObject::initCollisionSphere()
{
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
	if (physicsObject->collisionSphere)
	{
		// set collision sphere posisiton
		physicsObject->collisionSphere->_center = _position;
		return;
	}
	if (physicsObject->aabb)
	{
		// set aabb center pos ???


		physicsObject->aabb->_centerPosition = {
			(physicsObject->aabb->_max.x/2) + (physicsObject->aabb->_min.x/2), 
			(physicsObject->aabb->_max.y / 2) + (physicsObject->aabb->_min.y / 2), 
			(physicsObject->aabb->_max.z / 2) + (physicsObject->aabb->_min.z / 2) };
		glm::vec3 pos = physicsObject->aabb->_centerPosition;
		log("AABB center pos: " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z), LogLevel::DEBUG_V);
		return;
	}
	log("Physics object is invalid!!!", LogLevel::ERROR);
}
