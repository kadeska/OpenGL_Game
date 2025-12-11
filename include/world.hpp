#pragma once

#include <glm/glm.hpp>

#include "shader.hpp"
#include "entity/EntityCube.hpp"
#include "entity/entityChest.hpp"

class World
{
private:
	EntityChest* closestChest = nullptr;
	//EntityChest* currentChest = nullptr;
	//EntityChest* chestPtr = nullptr;
	EntityChest* newChest = nullptr;     // = EntityChest(-1, 0, glm::vec3(0, 0, 0), "null");

	glm::vec3 playerLocation;
	bool inRangeOfInteractable = false;
	bool shouldRenderInventory = false;

	std::vector<EntityCube> entityCubeVector;
	std::vector<EntityChest*> entityChestVector;

	// Creates a new EntityChest object at the given position with the specified size.
	// And returns a pointer to the created EntityChest object. 
	// Used to create chests when loading a world.
	EntityChest*& createChestAt(glm::vec3 _pos, int _size);

	// Add given chest entity object to the entityChestVector.
	// Used to add chests to the array to be rendered. 
	void addChest(EntityChest*& _chest);

	void createCube(glm::vec3 _pos);
	float getDistance(const glm::vec3& pos1, const glm::vec3& pos2);

	bool checkForClosestInteractable();

public:

	bool showInventory = false;

	/*
	 Parameterized constructor that allows setting the seed for world generation
	 and the size of the world.
	*/
	World(Shader* _shader, float _seed, int _worldSize);

	void init(Shader* _shader, float _seed, int _worldSize);

	void createWorld(float seed);
	void generateWorld(float seed);

	void saveWorld(std::string _filename);

	void updateWorld();

	// Add given cube entity onject to the entityCubeVector. 
	// Checks if ID = -1, as that means your trying to pass 
	// an uninisialized cube entity. EntityCube must be initialized 
	// using its parameterized constructor.
	void addCube(EntityCube _cube);

	

	void setPlayerPos(glm::vec3 _Playerpos);

	// Spawns a new EntityChest object at the given position if the 
	// location is available. 
	// Used to spawn a new chest in game. 
	void createChest(glm::vec3 _pos);

	void spawnPlayer(glm::vec3 _pos);

	bool isPositionOccupied(glm::vec3 _pos);

	bool checkPlayerCollisions();


	glm::vec3 getPlayerPos() { return playerLocation; }

	// Returns value of inRangeOfInteractable
	bool getInRangeOfInteracable();

	bool getShouldRenderInventory();

	EntityChest* getClosestChest();

	// Checks if the player is within interactRange of the given entityPosition.
	bool isInRange(glm::vec3 playerPosition, glm::vec3 entityPosition, float interactRange);


	std::vector<EntityCube> getEntityCubes() { return entityCubeVector; }

	std::vector<EntityChest*> getEntityChests() {
		return entityChestVector;
	}


	/*
	 Destructor to clean up any resources allocated for the world.
	 Can be used to delete this world, or unload from memory if making several worlds.
	 Makle sure to save the world before destroying it.
	*/
	~World();
};

