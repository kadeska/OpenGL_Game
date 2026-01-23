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

// the physics repersentation of the model
class GameObject
{
private:
	
	//Model* gameObjectModelPtr = nullptr;
	Sphere* collisionSphere = nullptr;
	AABB* aabb;
	bool useGravity = false;
	glm::vec3 velocity;
	Renderable::Renderable* gameObjectRenderable = nullptr;
	GO_Type type = GO_Type::T_NULL;

public:
	GameObject(GO_Type _type, glm::vec3 _position, Renderable::Renderable* _renderable);
	~GameObject() = default;
	glm::vec3 getPosition();
	void setPosition(glm::vec3 _position);

	GO_Type getType() { return type; }

	// returns the collision sphere, or nullptr
	Sphere* getCollisionSphere();
	void setCollisionSphere(Sphere* _sphere) { collisionSphere = _sphere; };
	AABB* getAABB() { return aabb; };
	void setAABB(AABB* _aabb) { aabb = _aabb; };
	bool getUseGravity() { return useGravity; }
	void setUseGravity(bool _useGravity) { useGravity = _useGravity; }
	Renderable::Renderable* getRenderable() { return gameObjectRenderable; }
	glm::vec3 getVelocity() { return velocity; }
	void setVelocity(glm::vec3 _velocity) { velocity = _velocity; }
	
};

