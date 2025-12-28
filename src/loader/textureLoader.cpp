#include <string>
#include <iostream>
#include <glad/glad.h>

#include "../misc/stb_image.h"

#include "textureLoader.hpp"
#include "../shader/shader.hpp"


#include "../misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;
// log("-- Constructor", LogLevel::DEBUG);



void TextureLoader::loadTextures(Shader*& _ourShader)
{
    log("Loading textures. !!(This function isnt needed at this time while we load models)", LogLevel::DEBUG);

    // Load and create a texture
    stbi_set_flip_vertically_on_load(true); // Flip textures vertically

    // Texture 1
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* texData = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (texData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: container.jpg" << std::endl;
    }
    stbi_image_free(texData);
    textures["container"] = texture1; // Store texture in the map

    // Texture 2
    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texData = stbi_load("textures/gray-tree-bark-64x64.jpg", &width, &height, &nrChannels, 0);
    if (texData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: gray-tree-bark-64x64.jpg" << std::endl;
    }
    stbi_image_free(texData);
    textures["bark"] = texture2; // Store texture in the map

    // Set texture samplers in the shader
    _ourShader->use();
    _ourShader->setInt("texture1", 0);
    _ourShader->setInt("texture2", 1);

}

GLuint TextureLoader::getTexture(const std::string& name) {
    return textures[name]; // Return the texture ID
}
