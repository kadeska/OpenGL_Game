#include "game3D.hpp"
#include "window/window.hpp"
#include "world/world.hpp"

//#include "window/input/inputManager.hpp"

#include "misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;
// log("-- Constructor", LogLevel::DEBUG);

Window* myWindow;
World* myWorld;

static const int WORLD_SIZE = 24;
static const float WORLD_SEED = 0;

static const float PLAYER_X = 5.0f;
static const float PLAYER_Y = 2.0f;
static const float PLAYER_Z = 5.0f;


Game3D::Game3D()
{
	log("Game3D Constructor", LogLevel::DEBUG);

    myWindow = new Window();
	
	myWindow->initialize(PLAYER_X, PLAYER_Y, PLAYER_Z);
	myWindow->createWindow();
}

Game3D::~Game3D()
{
}

void Game3D::start()
{
	myWindow->mainLoop(myWorld);
}

void Game3D::stop()
{
	myWindow->terminateWindow();
}
