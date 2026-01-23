#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "../physics/gameObject.hpp"
#include "../world/world.hpp"

struct Entity_Item 
{
	GameObject* go;
	glm::vec3 pos;
	unsigned int ID;
	unsigned int quantity;
};

struct Entity_Enemy 
{
	GameObject* go;
	glm::vec3 pos;
	unsigned int ID;
	unsigned int HP;
	unsigned int AP;
	// goal target

};

struct Entity_Friendly 
{
	GameObject* go;
	glm::vec3 pos;
	unsigned int ID;
	unsigned int HP;
};

class EntityManager
{
private:
	std::vector<Entity_Item*> itemArray;
	std::vector<Entity_Enemy*> enemyArray;
	std::vector<Entity_Friendly*> friendlyArray;

public:
	EntityManager(World* _world);
	~EntityManager() = default;

	void addEntityItem(Entity_Item* _item);
	void addEntityEnemy(Entity_Enemy* _enemy);
	void addEntityFriendly(Entity_Friendly* _friendly);

	

};

