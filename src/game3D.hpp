#pragma once
#include "misc/stateManager.hpp"
#include "render/loadingScreenRenderer.hpp"

class Game3D
{
public:
	// Make gameStateManager static to match its usage in game3D.cpp
	static StateManager::GameStateManager gameStateManager;

	
	
	// Empty game3D constructor only prepares the game systems. 
	// This is meant to be called first to get things ready such as 
	// loading OpenGL and creating the window system.
	Game3D();
	~Game3D();

	void setGameState(StateManager::GameState newState)
	{
		gameStateManager.setState(newState);
	}
	StateManager::GameState getGameState() const
	{
		return gameStateManager.getState();
	}

	LoadingScreenRenderer* getLoadingScreenRenderer();

	//---------------------------------------------
	//---------------------------------------------


	// Initializes the game systems and gets ready for rendering.
	bool initializeGameWindow();
	/*
	Starts the main game loop.
	*/
	void start();
	void stop();
};

