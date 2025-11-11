#pragma once

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "../include/shaderProgram.hpp"
#include "shader.hpp"
#include "textureLoader.hpp"
#include "../include/world.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


/*
 Class: Window
 ----------------
 This class handles creation and management of the application window using GLFW.
 It includes methods for initializing GLFW, creating the window, loading OpenGL functions,
 running the main rendering loop, processing input, and terminating the window.

*/
class Window
{
public:
	// FreeType
	// --------
	FT_Library ft;

	// settings

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	GLFWwindow* window;
	//ShaderProgram* shaderProgram;
	Shader* ourShader;
	Shader* textShader;
	TextureLoader textureLoader;

	// functions
	// Must call these functions in this spacific order.
	// ---------------------------------------------------

	void initialize(float _camX, float _camY, float _camZ);
	void createWindow();
	void loadOpenGL();
	void createShaderProgram();
	int initFreeType();


	void mainLoop(World* _world);
	void RenderText(Shader* shader, std::string text, float x, float y, float scale, glm::vec3 color);
	void terminateWindow();

	// ---------------------------------------------------

private:

	void processInput(GLFWwindow* window, World* _world);
	void render();

};


