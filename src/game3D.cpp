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

StateManager::GameStateManager Game3D::gameStateManager;
LoadingScreenRenderer* loadingScreenRenderer = nullptr;


static void onEnterLoading()
{
	// do loading tasks here
	log("LOADING", LogLevel::STATE);
}

static void onExitLoading()
{
	//myWorld = new World();
}

Game3D::Game3D()
{
	myWindow = new Window(gameStateManager);
	loadingScreenRenderer = new LoadingScreenRenderer(myWindow);

	myWindow->setLoadingRenderer(loadingScreenRenderer);
	myWindow->initialize(5.0f, 2.0f, 5.0f);
	myWindow->createWindow();
	loadingScreenRenderer->init();

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


LoadingScreenRenderer* Game3D::getLoadingScreenRenderer()
{
	return loadingScreenRenderer;
}

bool Game3D::initializeGameWindow()
{
	log("Game3D Constructor_2", LogLevel::DEBUG);
	myWindow = new Window(gameStateManager);

	myWindow->initialize(PLAYER_X, PLAYER_Y, PLAYER_Z);
	myWindow->createWindow();

	return true;
}

void Game3D::start()
{
	myWindow->mainLoop(myWorld);
}

void Game3D::stop()
{
	myWindow->terminateWindow();
}


