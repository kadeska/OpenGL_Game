#pragma once
#include <vector>
#include "../physics/gameObject.hpp"

struct WorldData 
{
	std::string saveFilePath;
	std::vector<GameObject*> gameObjects;
};

class World
{
public:
	World();
	~World();
	void update();

private:
	WorldData worldData;
};

