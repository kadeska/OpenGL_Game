#pragma once

#include <string>


#include "../include/shader.hpp"



class TextRenderer
{
public:

	TextRenderer();
	~TextRenderer();

	int renderText(std::string& _text, Shader*& shader, 
		glm::vec3& color, float x, float y, float scale, 
		int _screenWidth, int _screenHeight, std::string& _fontFilePath);
};