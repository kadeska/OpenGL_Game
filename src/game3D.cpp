#include "game3D.hpp"
#include "window/window.hpp"
#include "world/world.hpp"
#include "render/loadingScreenRenderer.hpp"
#include "misc/stateManager.hpp"
#include "misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;

static const int WORLD_SIZE = 24;
static const float WORLD_SEED = 0;

static const float PLAYER_X = 5.0f;
static const float PLAYER_Y = 2.0f;
static const float PLAYER_Z = 5.0f;

Window* myWindow;
World* myWorld;

LoadingScreenRenderer* loadingScreenRenderer = nullptr;

StateManager::GameStateManager Game3D::gameStateManager;

static void onEnterLoading()
{
	loadingScreenRenderer = new LoadingScreenRenderer(myWindow);
}

static void onExitLoading()
{
	//myWorld = new World();
}

Game3D::Game3D()
{
	myWindow = new Window(gameStateManager);
	myWindow->initialize(5.0f, 2.0f, 5.0f);
	myWindow->createWindow();

	gameStateManager.onEnter(StateManager::GameState::LOADING, onEnterLoading);
	gameStateManager.onExit(StateManager::GameState::LOADING, onExitLoading);

	gameStateManager.setState(StateManager::GameState::LOADING);
}

Game3D::~Game3D()
{
}

//void Game3D::renderLoadingScreenCallback()
//{
//	log("Render Loading Screen Callback");
//	if (!loadingScreenRenderer) 
//	{
//		log("Initializing loadingScreenRenderer...");
//		loadingScreenRenderer = new LoadingScreenRenderer(myWindow);
//		return;
//	}
//	loadingScreenRenderer->renderLoadingScreen();
//	// After loading is done, create the world
//	log("Done loading game data...");
//	gameStateManager.setState(StateManager::GameState::PLAYING); // Now valid, as static
//	//glfwTerminate();
//}


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


