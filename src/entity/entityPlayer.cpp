
#include "../misc/programLogger.hpp"

#include "entityPlayer.hpp"

using ProgramLogger::log;
using ProgramLogger::LogLevel;

EntityPlayer::EntityPlayer(glm::vec3 _playerLocation)
{
	log("EntityPlayer constructor", LogLevel::DEBUG);
}
