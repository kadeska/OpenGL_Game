#pragma once
#include <vector>
#include <string>

#include "../physics/collisionTests.hpp"
#include "../shader/shader.hpp"
#include "mesh/mesh.hpp"

#include <assimp/scene.h>

unsigned int TextureFromFile(const char* _path, const std::string& _directory, bool _gamma = false);

enum class Model_Type
{
	GROUND,
	DONUT,
	BACKPACK
};

class Model
{
public:
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh>    meshes;
	std::string directory;

	bool gammaCorrection;

	// Model requires the path to the model, and an ID
	// ID is used for filtering
	Model(const char* _path, Model_Type _type);
	void Draw(Shader& _shader);

	Model_Type getModelType() { return this->type; }
	void setModelType(Model_Type _type) { type = _type; }
	
private:
	
	Model_Type type;

	void loadModel(std::string _path);
	void processNode(aiNode* _node, const aiScene* _scene);
	Mesh processMesh(aiMesh* _mesh, const aiScene* _scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* _mat, aiTextureType _type, std::string _typeName);
};

