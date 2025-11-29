#include <iostream>

#include "../include/game3D.hpp"

#include "../include/programLogger.hpp"


// for testing
//#include "../include/FileManager.hpp"


//#include <ft2build.h>
//#include FT_FREETYPE_H

//int loadFreeType();



using::ProgramLogger::log;
using::ProgramLogger::LogLevel;



//Game3D* myGame3D;

void printMaxVertexAttributes()
{
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;
	log("Maximum number of vertex attributes supported: " + std::to_string(nrAttributes));
}

int main()
{
	//loadFreeType();

	Game3D* myGame3D = new Game3D();
	printMaxVertexAttributes();
	myGame3D->start();
	myGame3D->stop();
	
    return 0;
}



//int loadFreeType() 
//{
//	log("Loading FreeType...");
//	FT_Library ft;
//	if (FT_Init_FreeType(&ft))
//	{
//		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//		return -1;
//	}
//
//	//FT_Face face;
//	//if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
//	//{
//	//	std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//	//	return -1;
//	//}
//
//	//FT_Set_Pixel_Sizes(face, 0, 48);
//}
