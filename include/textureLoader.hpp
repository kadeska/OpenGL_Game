#pragma once

#include "../include/shader.hpp"


class TextureLoader
{

public:
	std::unordered_map<std::string, GLuint> textures;
	void loadTextures(Shader* _ourShader);
	GLuint getTexture(const std::string& name);
	int width, height, nrChannels;
};

