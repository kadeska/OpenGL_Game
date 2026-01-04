#pragma once
#include <string>
#include "../world/world.hpp"
class WorldGenerator
{
public:
	WorldGenerator();
	~WorldGenerator() = default;

	void generateDefaultWorld(World*& _worldPtrRef);
	void generateWorldFromConfig(World*& _worldPtrRef, const std::string& configData);
};

