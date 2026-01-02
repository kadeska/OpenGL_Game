#include <iostream>

#include <glad/glad.h>

#include "game3D.hpp"
#include "misc/programLogger.hpp"
using::ProgramLogger::log;
using::ProgramLogger::LogLevel;

static int state;


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

	// I should first initialize a system file manager for cross-platform file handling.
	// render loading screen? ---------------
	// load assets --------------------------
	// enter main menu state ----------------
	// game loop ----------------------------
	// --------------------------------------


	// initialize game
	Game3D* myGame3D = new Game3D();
	// print max vertex attributes for debugging
	printMaxVertexAttributes();
	// start game loop
	myGame3D->start();
	// clean up and exit
	myGame3D->stop();


	// I do the following below to keep the console window open until the user presses any button.

	std::cout << '\n' << "Game has quit, press any button to close console... " << '\n';

	std::cin.get(); // wait for user input before closing console
	
    return 0;
}