#include "game3D.hpp"
#include "window/window.hpp"
#include "world/world.hpp"

#include "render/loadingScreenRenderer.hpp"

//#include "window/input/inputManager.hpp"

#include "misc/stateManager.hpp"
#include "misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;
// log("-- Constructor", LogLevel::DEBUG);


LoadingScreenRenderer* loadingScreenRenderer = nullptr;


Window* myWindow;
World* myWorld;

static const int WORLD_SIZE = 24;
static const float WORLD_SEED = 0;

static const float PLAYER_X = 5.0f;
static const float PLAYER_Y = 2.0f;
static const float PLAYER_Z = 5.0f;


Game3D::Game3D()
{
	log("Game3D Constructor_1", LogLevel::DEBUG);
	
	// initialize game state manager

	gameStateManager = StateManager::GameStateManager();

	// initialize window

	myWindow = new Window(gameStateManager);
	myWindow->initialize(PLAYER_X, PLAYER_Y, PLAYER_Z);
	myWindow->createWindow();

	// register callbacks

	gameStateManager.registerRenderLoadingScreenCallback(renderLoadingScreenCallback);

	// set initial game state to LOADING

	gameStateManager.setState(StateManager::GameState::LOADING);

}

Game3D::~Game3D()
{
}

void Game3D::renderLoadingScreenCallback()
{
	log("Render Loading Screen Callback");
	if (!loadingScreenRenderer) 
	{
		log("Initializing loadingScreenRenderer...");
		loadingScreenRenderer = new LoadingScreenRenderer();
	}
}


bool Game3D::initializeGameWindow()
{
	log("Game3D Constructor_2", LogLevel::DEBUG);
	myWindow = new Window(gameStateManager);

	myWindow->initialize(PLAYER_X, PLAYER_Y, PLAYER_Z);
	myWindow->createWindow();

	return false;
}

void Game3D::start()
{
	myWindow->mainLoop(myWorld);
}

void Game3D::stop()
{
	myWindow->terminateWindow();
}
