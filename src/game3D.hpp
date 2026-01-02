#pragma once
#include "misc/stateManager.hpp"

class Game3D
{
public:
	StateManager::GameStateManager gameStateManager;
	
	// Empty game3D constructor only prepares the game systems. 
	// This is meant to be called first to get things ready such as 
	// loading OpenGL and creating the window system.
	Game3D();
	~Game3D();

	//---------------------------------------------
	// Callback Functions
	//--------------------------------------------- 
	//
	// Callback function for rendering the loading screen.
	static void renderLoadingScreenCallback();
	// Callback function for rendering the main menu.
	static void renderMainMenuCallback();
	// Callback function for rendering the game world.
	static void renderGameWorldCallback();
	// Callback function for rendering the pause menu.
	static void renderPauseMenuCallback();
	// Callback function for rendering the game over screen.
	static void renderGameOverScreenCallback();
	//
	//---------------------------------------------
	// Input Handling Callbacks
	//---------------------------------------------
	//
	// Callback function for handling input in the main menu.
	static void mainMenuInputCallback();
	// Callback function for handling input in the game world.
	static void gameWorldInputCallback();
	// Callback function for handling input in the pause menu.
	static void pauseMenuInputCallback();
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

