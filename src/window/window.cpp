#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Window.hpp"
#include "input/inputManager.hpp"
#include "../render/sceneRenderer.hpp"
#include "../misc/programLogger.hpp"
#include "../misc/stateManager.hpp"

using ProgramLogger::log;
using ProgramLogger::LogLevel;

using namespace StateManager;

// make sure to only have one instance of GameStateManager, here we have a referance to it.
// the ref points to the StateManager in game3D.cpp
GameStateManager gameState;
World* world = nullptr;

// --------------------------------------------------------
// GLFW Callbacks
// --------------------------------------------------------
namespace {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (!window) return;

        // Retrieve InputManager from window user pointer
        auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
        if (inputManager && gameState.is(GameState::PLAYING))
            inputManager->processMouseMovement(xpos, ypos);
    }

    void scroll_callback(GLFWwindow* window, double /*xoffset*/, double yoffset)
    {
        if (!window) return;

        auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
        if (inputManager && gameState.is(GameState::PLAYING))
            inputManager->processMouseScroll(yoffset);
    }

} // namespace

Window::Window(StateManager::GameStateManager& _gameStateManager)
{
    log("Window constructor", LogLevel::DEBUG);
	gameState = _gameStateManager;
}

// --------------------------------------------------------
// Window Methods
// --------------------------------------------------------
void Window::initialize(float _camX, float _camY, float _camZ)
{
    log("Window initializer", LogLevel::DEBUG);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //stbi_set_flip_vertically_on_load(true);

}

//void Window::initSceneRenderer()
//{
//    // Initialize scene renderer
//    sceneRenderer = std::make_unique<SceneRenderer>(SCR_WIDTH, SCR_HEIGHT);
//
//}

void Window::createWindow()
{
    // 1. Create GLFW window
    GLFWwindow* win = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (!win)
    {
        log("Failed to create GLFW Window", LogLevel::ERROR);
        glfwTerminate();
        return;
    }

    window.reset(win);
    glfwMakeContextCurrent(window.get());

	// now that contexts exist, we can load OpenGL functions
	loadOpenGL();

    //// 2. Initialize sceneRenderer first
    //sceneRenderer = std::make_unique<SceneRenderer>(SCR_WIDTH, SCR_HEIGHT);

    //// 3. Initialize InputManager
    //inputManager = std::make_unique<InputManager>(window.get(), *sceneRenderer);

    //// 4. Attach InputManager pointer to window user pointer for callbacks
    //glfwSetWindowUserPointer(window.get(), inputManager.get());

    //// 5. Set GLFW callbacks (now safe, because objects exist)
    //glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
    //glfwSetCursorPosCallback(window.get(), mouse_callback);
    //glfwSetScrollCallback(window.get(), scroll_callback);

    //// 6. Set cursor input mode
    //glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //log("Window created and callbacks set", LogLevel::DEBUG);
    log("Window created", LogLevel::DEBUG);
}


void Window::loadOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log("Failed to initialize GLAD", LogLevel::ERROR);
        return;
    }
    log("OpenGL functions have been loaded successfuly", LogLevel::DEBUG);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void Window::imGuiNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::createShaderProgram()
{
    log("CreateShaderProgram is no longer needed", LogLevel::WARNING);
}

void Window::loadTextures()
{
    log("loadTextures is no longer needed", LogLevel::WARNING);
}

void Window::mainLoop(World* _world)
{
	world = _world;
	//gameState.setState(GameState::MainMenu);

	if (!_world) // if the world has not been created yet
    {
        log("World pointer is null in Window::mainLoop", LogLevel::ERROR);
        // Render main menu
        //return;
    }

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window.get()))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /*if (gameState.is(GameState::None)) 
        {
			log("GameState is None.", LogLevel::INFO);
        }*/

        update();
        //processInput(_world);

        //sceneRenderer->RenderScene();

        glfwSwapBuffers(window.get());
        glfwPollEvents();

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
            std::cout << "OpenGL error: " << err << std::endl;
    }
}

void Window::cleanupImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Window::terminateWindow()
{
    glfwTerminate();
}

void Window::update()
{
	inputManager->checkESCToggle();

    if (gameState.is(GameState::PAUSED)) 
    {
		log("GameState is Paused", LogLevel::STATE);
    }

    if (gameState.is(GameState::MAIN_MENU))
    {
        // here we are in the main menu state, so render the main menu and process menu inputs
        log("GameState is mainMenu", LogLevel::STATE);
		gameState.setState(GameState::PLAYING);

    }

    if (gameState.is(GameState::PLAYING))
    {
        log("GameState is Playing", LogLevel::STATE);
        processInput(world);
        sceneRenderer->RenderScene();
    }

    if (gameState.is(GameState::GAME_OVER)) 
    {
		log("GameState is GameOver", LogLevel::STATE);
    }
}

void Window::processInput(World* _world)
{
    if (!inputManager)
    {
        log("InputManager is null...", LogLevel::ERROR);
    }

	inputManager->checkESCToggle();
    inputManager->processInput(deltaTime);


    
}
