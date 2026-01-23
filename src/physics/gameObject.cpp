#include "gameObject.hpp"
#include "../misc/programLogger.hpp"
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

AABB* goAABB = new AABB{ {0,0,0},{0,0,0} };
Sphere* goSphere = new Sphere{ {0,0,0}, 0 };

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

	// set that game objects renderable object
	gameObjectRenderable = _renderable;

	// set game objects position 
	setPosition(_position);

	// figure out what type of collission object to use based off of go_type
	// do type spacific stuff

	glm::vec3 maxVertPos = {0,0,0};
	glm::vec3 minVertPos = {0,0,0};

	glm::vec3 prevVertPos = {0,0,0};
	glm::vec3 currentVertPos = {0,0,0};

	switch (_type)
	{
	case GO_Type::T_NULL:
		log("WARNING: GO type given is null. Did you mean to do this?", LogLevel::DEBUG_V);
		//return;
		break;
	case GO_Type::PLAYER:
		break;
	case GO_Type::HOSTILE:
		break;
	case GO_Type::GROUND:
		log("Setting up GROUND", LogLevel::DEBUG_V);
		// go through the list of meshes and for each mesh, 
		// go through its list of vertices and find the Max and Min values
		for (int mesh_index = 0; mesh_index < gameObjectRenderable->model->meshes.size(); mesh_index++)
		{
			// do something for the mesh at index i
			for (int vert_index = 0; vert_index < gameObjectRenderable->model->meshes[mesh_index].vertices.size(); vert_index++)
			{
				// for every vertex in this mesh

				// set current pos of the vertex we are testing
				currentVertPos = gameObjectRenderable->model->meshes[mesh_index].vertices[vert_index].Position;

				// max test ---

				// if this vertex is greater than the previus vertex, then set max pos to current pos
				if ((currentVertPos.y > prevVertPos.y) || (currentVertPos.x > prevVertPos.x) || (currentVertPos.z > prevVertPos.z)) 
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
				if ((currentVertPos.y < prevVertPos.y) || (currentVertPos.x < prevVertPos.x) || (currentVertPos.z < prevVertPos.z)) 
				{
					minVertPos = currentVertPos;
					prevVertPos = currentVertPos;
				}

				// end of tests ---
			}
		}
		// set bounding box min and max posisions.
		log("bounding box Min X: " + std::to_string(minVertPos.x) + " , Y: " + std::to_string(minVertPos.y) + " , Z: " + std::to_string(minVertPos.z), LogLevel::DEBUG_V);
		goAABB->_min = minVertPos; // set the bounding box min pos
		log("bounding box Man X: " + std::to_string(maxVertPos.x) + " , Y: " + std::to_string(maxVertPos.y) + " , Z: " + std::to_string(maxVertPos.z), LogLevel::DEBUG_V);
		goAABB->_max = maxVertPos; // set bounding box max pos
		setAABB(goAABB);
		break;
	case GO_Type::WALL:
		break;
	case GO_Type::ITEM:
		//aabb = new AABB(glm::vec3(0,0,0), glm::vec3(3,3,3)); // set the bounding box 
		break;
	default:
		break;
	}

	type = _type;
}

Sphere* GameObject::getCollisionSphere()
{
	if (!collisionSphere)
	{
		// log("model collision sphere is null", logLevel::ERROR);
		return nullptr;
	}
	return collisionSphere;
}

glm::vec3 GameObject::getPosition()
{
	return collisionSphere->_center;
}

void GameObject::setPosition(glm::vec3 _position)
{
	collisionSphere->_center = _position;
}
