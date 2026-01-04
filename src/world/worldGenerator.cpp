#include "worldGenerator.hpp"
#include "../misc/programLogger.hpp"
#include "world.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;

WorldGenerator::WorldGenerator()
{
	log("WorldGenerator constructor", LogLevel::DEBUG);
}

void WorldGenerator::generateDefaultWorld(World*& _worldPtrRef)
{
	log("Loading/generating default world...", LogLevel::DEBUG);
	_worldPtrRef = new World();
	return;
}
