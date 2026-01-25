#pragma once
#include "collisionTests.hpp"
#include "../model/model.hpp"
#include "../render/renderable.hpp"

enum class GO_Type
{
	T_NULL,
	PLAYER,
	HOSTILE,
	FRIENDLY,
	GROUND,
	WALL,
	ITEM
};

struct PhysicsObject 
{
	Sphere* collisionSphere = nullptr;
	AABB* aabb = nullptr;
};

// the physics repersentation of the model
class GameObject
{
private:
	
	glm::vec3 maxVertPos = { 0,0,0 };
	glm::vec3 minVertPos = { 0,0,0 };

	glm::vec3 prevVertPos = { 0,0,0 };
	glm::vec3 currentVertPos = { 0,0,0 };

	//Model* gameObjectModelPtr = nullptr;
	//Sphere* collisionSphere = nullptr;
	//AABB* aabb = nullptr;
	bool useGravity = false;
	glm::vec3 velocity;
	Renderable::Renderable* gameObjectRenderable = nullptr;
	GO_Type type = GO_Type::T_NULL;

	PhysicsObject* physicsObject;

	void initAABB();
	void initCollisionSphere();

public:
	GameObject(GO_Type _type, glm::vec3 _position, Renderable::Renderable* _renderable);
	~GameObject() = default;
	glm::vec3 getPosition();
	void setPosition(glm::vec3 _position);

	GO_Type getType() { return type; }

	// returns the collision sphere, or nullptr
	Sphere* getCollisionSphere();
	void setCollisionSphere(Sphere* _sphere) { physicsObject->collisionSphere = _sphere; };
	AABB* getAABB() { return physicsObject->aabb; };
	void setAABB(AABB* _aabb) { physicsObject->aabb = _aabb; };
	bool getUseGravity() { return useGravity; }
	void setUseGravity(bool _useGravity) { useGravity = _useGravity; }
	Renderable::Renderable* getRenderable() { return gameObjectRenderable; }
	glm::vec3 getVelocity() { return velocity; }
	void setVelocity(glm::vec3 _velocity) { velocity = _velocity; }
	
};

