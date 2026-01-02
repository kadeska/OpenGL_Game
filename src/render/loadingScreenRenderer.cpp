#include "loadingScreenRenderer.hpp"
#include "../shader/shader.hpp"

#include "../misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;

Shader* loadingScreenShader = nullptr;

LoadingScreenRenderer::LoadingScreenRenderer()
{
	log("LoadingScreenRenderer constructor", LogLevel::DEBUG);
	loadingScreenShader = new Shader("shaders/textVertexShader.vs", "shaders/textFragmentShader.fs");
}

void LoadingScreenRenderer::renderLoadingScreen()
{
}
