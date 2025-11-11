#include <iostream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Window.hpp"
#include "../include/shader.hpp"
#include "../include/textureLoader.hpp"
#include "../include/camera3D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/programLogger.hpp"
using ProgramLogger::log;

// FreeType
// --------
FT_Library ft;

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters;


// camera stuff


Camera3D* myCamera;// = new Camera3D(glm::vec3(CAM_X, CAM_Y, CAM_Z));
float lastX;
float lastY;
bool firstMouse = true;

// timing

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


void Window::initialize(float _camX, float _camY, float _camZ)
{

    myCamera = new Camera3D(glm::vec3(_camX, _camY, _camZ));

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;



    //initFreeType();
    //configureFreeType();


    // glm test
   /* glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;*/

}

void Window::createShaderProgram()
{
    //shaderProgram = new ShaderProgram();
	//shaderProgram->makeShaderProgram();

    //Shader ourShader("", "");
	ourShader = new Shader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
    ourShader->setUp();
	textureLoader.loadTextures(ourShader);


    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textShader = new Shader("shaders/textVertexShader.vs", "shaders/textFragmentShader.fs");

    // After creating textShader in Window::createShaderProgram
    glGenVertexArrays(1, &textShader->textVAO);
    glGenBuffers(1, &textShader->textVBO);
    glBindVertexArray(textShader->textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textShader->textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    textShader->use();
    glUniformMatrix4fv(glGetUniformLocation(textShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}

int Window::initFreeType()
{
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    // find path to font
    std::string font_name = "fonts/arial.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return -1;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Window::configureFreeType()
{
    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &textShader->textVAO);
    glGenBuffers(1, &textShader->textVBO);
    glBindVertexArray(textShader->textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textShader->textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Window::createWindow()
{
    // glfw Window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return; // -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::loadOpenGL()
{
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;// -1;
    }
}

void Window::mainLoop(World* _world)
{

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        processInput(window, _world);


		myCamera->applyGravity(deltaTime);
		myCamera->updatePosition(deltaTime);

		_world->setPlayerPos(myCamera->camPos);


        _world->updateWorld();

        // Rendering commands here
		// ----------------------
        render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cout << "OpenGL error: " << err << std::endl;
        }
    }
}

void Window::render() 
{
    // clear screen
	// ------

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);

    // Activate and Bind Textures
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLoader.texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureLoader.texture2);

	// Use shader program
	ourShader->use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    
    glm::mat4 projection = glm::perspective(glm::radians(myCamera->camZoomLevel), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader->setMat4("projection", projection);

    // camera/view transformation

    glm::mat4 view = myCamera->GetViewMatrix();
    ourShader->setMat4("view", view);

    // render cubes
	// ------------------------------

    glBindVertexArray(ourShader->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // no longer use glDrawElements as we no longer want to use an EBO
    // 
    
    for (unsigned int i = 0; i < ourShader->vertData.cubePositions.size(); i++) 
    {
        // calculate the model matrix for each object and pass it the shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, ourShader->getCubeAt(i));
        float angle = 0; // 20.0f * i;
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

	//glBindVertexArray(0); // no need to unbind it every time




    // render text
    // -----------------------------
    

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //textShader->setInt("text", 0); // Add this before rendering text

    // src/window.cpp (in render or after rendering 3D objects)
    RenderText(textShader, "Hello World", 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
}


void Window::RenderText(Shader* shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    shader->use();
    glUniform3f(glGetUniformLocation(shader->ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(shader->textVAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, shader->textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
}

void Window::terminateWindow()
{
	// call deallocateResources from shaderProgram.cpp to free resources
	ourShader->deallocateResources();

    glfwTerminate();
}

bool paused = false;
static bool escPrevPressed = false;
static bool spacePrevPressed = false;
static bool toggleGravityPressed = false;

void Window::processInput(GLFWwindow* _window, World* _world)
{
    

    // ESC key edge detection

    bool escPressed = glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
    if (escPressed && !escPrevPressed) // Only on transition from not pressed to pressed
    {
        if (!paused)
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            paused = true;
        }
        else
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true; // to prevent sudden camera jump.  // Needs fixing, doesnt work like expected. Maybe store lastX and lastY when pausing?
            paused = false;
        }
    }
    escPrevPressed = escPressed; // Update previous state

    // SPACE key edge detection

    bool spacePressed = glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS;
    if (spacePressed && !spacePrevPressed) // Only on transition from not pressed to pressed
    {
        log("Space key pressed");
        //_world->spawnEntityCubeAt(_world->snapToGrid(myCamera->camPos));
        _world->spawnEntityCubeAt(myCamera->camPos);
    }
    spacePrevPressed = spacePressed; // Update previous state


    bool toggleGravity = glfwGetKey(_window, GLFW_KEY_G) == GLFW_PRESS;
    if (toggleGravity && !toggleGravityPressed) 
    {
        //log("Gravity toggled");
        //myCamera->useGravity = true;
        if (!myCamera->useGravity) 
        {
            myCamera->useGravity = true;
            log("Gravity toggled on");
        } 
        else 
        {
            myCamera->useGravity = false;
            log("Gravity toggled off");
        }
    }
    toggleGravityPressed = toggleGravity;
    

    // Movement keys (continuous)
    /*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
    {
        myCamera->ProcessKeyboard(FORWARD, deltaTime);
    }
        
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
    {
        myCamera->ProcessKeyboard(BACKWARD, deltaTime);
    }
        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
    {
        myCamera->ProcessKeyboard(LEFT, deltaTime);
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
    {
        myCamera->ProcessKeyboard(RIGHT, deltaTime);
    }*/

    // Movement keys (continuous)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        float velocity = myCamera->camMovementSpeed * deltaTime;
        glm::vec3 moveVec = myCamera->camFront * velocity;
        glm::vec3 intendedPos = myCamera->camPos + moveVec;
        glm::vec3 checkPos = intendedPos + glm::normalize(myCamera->camFront) * myCamera->collisionRadius;
        glm::vec3 gridCheckPos = _world->snapToGrid(checkPos);
        if (!_world->isPositionOccupied(gridCheckPos)) {
            myCamera->camPos = intendedPos;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        float velocity = myCamera->camMovementSpeed * deltaTime;
        glm::vec3 moveVec = -myCamera->camFront * velocity;
        glm::vec3 intendedPos = myCamera->camPos + moveVec;
        glm::vec3 checkPos = intendedPos - glm::normalize(myCamera->camFront) * myCamera->collisionRadius;
        glm::vec3 gridCheckPos = _world->snapToGrid(checkPos);
        if (!_world->isPositionOccupied(gridCheckPos)) {
            myCamera->camPos = intendedPos;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        float velocity = myCamera->camMovementSpeed * deltaTime;
        glm::vec3 moveVec = -myCamera->camRight * velocity;
        glm::vec3 intendedPos = myCamera->camPos + moveVec;
        glm::vec3 checkPos = intendedPos - glm::normalize(myCamera->camRight) * myCamera->collisionRadius;
        glm::vec3 gridCheckPos = _world->snapToGrid(checkPos);
        if (!_world->isPositionOccupied(gridCheckPos)) {
            myCamera->camPos = intendedPos;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        float velocity = myCamera->camMovementSpeed * deltaTime;
        glm::vec3 moveVec = myCamera->camRight * velocity;
        glm::vec3 intendedPos = myCamera->camPos + moveVec;
        glm::vec3 checkPos = intendedPos + glm::normalize(myCamera->camRight) * myCamera->collisionRadius;
        glm::vec3 gridCheckPos = _world->snapToGrid(checkPos);
        if (!_world->isPositionOccupied(gridCheckPos)) {
            myCamera->camPos = intendedPos;
        }
    }
        
}

void framebuffer_size_callback(GLFWwindow* Window, int width, int height)
{
    // make sure the viewport matches the new Window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    myCamera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    myCamera->ProcessMouseScroll(static_cast<float>(yoffset));
}