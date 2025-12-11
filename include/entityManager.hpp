#pragma once
class EntityManager
{
private:

public:
	EntityManager();
	~EntityManager() = default;

	void createEntityCube(glm::vec3 _cubeLocation);
	void createEntityChest(glm::vec3 _cubeLocation);
	void createEntityPlayer(glm::vec3 _cubeLocation);


	// ---------------------------------------------------------------UTILITIES---------------------------------------------------------
	
	bool isPositionOccupied(glm::vec3 _pos);
	glm::vec3 snapToGrid(glm::vec3& pos);
};

