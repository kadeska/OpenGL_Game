#include "loadingScreenRenderer.hpp"
#include "../window/window.hpp"
#include "../shader/shader.hpp"
#include "textRenderer.hpp"

static Shader* shader = nullptr;
static TextRenderer* textRenderer = nullptr;

std::string text = "Loading...";
std::string path = "fonts/arial.ttf";
glm::vec3 color = {12, 0, 0};

LoadingScreenRenderer::LoadingScreenRenderer(Window* _window)
    : window(_window)
{
    shader = new Shader(
        "shaders/textVertexShader.vs",
        "shaders/textFragmentShader.fs"
    );
    textRenderer = new TextRenderer();
}

void LoadingScreenRenderer::render()
{
    textRenderer->renderText(text, shader, color, window->getScreenWidth() / 2 - 80, window->getScreenHeight() / 2, 1.0f, window->getScreenWidth(), window->getScreenHeight(), path);
}
