#include <iostream>

#include <glad/glad.h>

#include "game3D.hpp"
#include "misc/programLogger.hpp"
using::ProgramLogger::log;
using::ProgramLogger::LogLevel;


//static void bar(int a) 
//{
//	std::cout << "Value: " << a << std::endl;
//}


// Must be called after loading OpenGL functions.
// In this case, after the window loads OpenGL, 
// which takes place in the constructor of Game3D.
void printMaxVertexAttributes()
{
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;
	log("Maximum number of vertex attributes supported: " + std::to_string(nrAttributes));
}


int main(int argc, char* argv[])
{
	log("Main entry", LogLevel::DEBUG);

	//ProgramLogger::foo(log);

	// I should first initialize a system file manager for cross-platform file handling.
	// render loading screen? ---------------
	// load assets --------------------------
	// enter main menu state ----------------
	// game loop ----------------------------
	// --------------------------------------


	// initialize game
	Game3D* game = new Game3D();
	//printMaxVertexAttributes();
	game->start();
	game->stop();


	// I do the following below to keep the console window open until the user presses any button.
	std::cout << '\n' << "Game quit in State: " + std::to_string(static_cast<int>(game->gameStateManager.getState())) << '\n';
	// if the game quit during loading, RIP any save data that might be corupted 
	std::cout << '\n' << "Game has quit, press any button to close console... " << '\n';

	std::cin.get(); // wait for user input before closing console
	
    return 0;
}