#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include "../camera/camera3D.hpp"
#include "../shader/shader.hpp"
#include "../model/model.hpp"

#include "sceneRenderer.hpp"



// the vector of models to use for rendering each gameObject.
// Do not create multiple Model objects for the same model, 
// we only use these Model objects to get the meshes for rendering

// Positions of every Backpack model
std::vector<glm::vec3> backpackPositions = {
    { 5.0f, 3.0f, 1.0f },
    { 2.0f, 3.0f, -4.0f },
    { -3.0f, 3.0f, -2.0f },
    { 0.0f, 3.0f, 5.0f }
};

// Positions of every Donut model
std::vector<glm::vec3> donutPositions = {
    { 1.0f, 7.0f, 12.0f },
    { 10.0f, 2.0f, -1.0f }
};


//SceneRenderer::SceneRenderer(const unsigned int _screenWidth, const unsigned int _screenHeight)
//{
//    // load models
//    models.push_back(std::make_unique<Model>("models/backpack/backpack.obj"));
//    models.push_back(std::make_unique<Model>("models/donut/donut.obj"));
//
//    // camera
//    sceneWidth = _screenWidth;
//    sceneHeight = _screenHeight;
//    camera = std::make_unique<Camera3D>(glm::vec3(5.0f, 2.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, -30.0f);
//
//    // shaders
//    //log("Creating shader programs for scene and text", LogLevel::DEBUG);
//    sceneShader = std::make_unique<Shader>("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
//    textShader = std::make_unique<Shader>("shaders/textVertexShader.vs", "shaders/textFragmentShader.fs");
//}

SceneRenderer::SceneRenderer(unsigned int w, unsigned int h)
{
    sceneWidth = w;
    sceneHeight = h;

    models.push_back(std::make_unique<Model>("models/backpack/backpack.obj"));
    models.push_back(std::make_unique<Model>("models/donut/donut.obj"));

    camera = std::make_unique<Camera3D>(
        glm::vec3(0.0f, 2.0f, 10.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        0.0f
    );

    sceneShader = std::make_unique<Shader>(
        "shaders/vertexShader.vs",
        "shaders/fragmentShader.fs"
    );

    // Populate renderables
    for (const glm::vec3& pos : backpackPositions)
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, pos);

        renderables.push_back({
            models[0].get(),
            transform
            });
    }
}

void SceneRenderer::RenderScene()
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sceneShader->use();

    glm::mat4 projection = glm::perspective(
        glm::radians(camera->getCamZoom()),
        (float)sceneWidth / (float)sceneHeight,
        0.1f,
        100.0f
    );

    glm::mat4 view = camera->GetViewMatrix();
    sceneShader->setMat4("projection", projection);
    sceneShader->setMat4("view", view);

    // Draw multiple models
    for (const Renderable& r : renderables) {
        sceneShader->setMat4("model", r.transform);
        r.model->Draw(*sceneShader);
    }
    /*for (const glm::vec3& pos : backpackPositions)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, glm::vec3(1.0f));

        sceneShader->setMat4("model", model);

        models.at(0)->Draw(*sceneShader); 
    }*/
}

Camera3D& SceneRenderer::getCamera()
{
    return *camera;
}
