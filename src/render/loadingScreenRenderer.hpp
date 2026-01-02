#pragma once
class Window;

class LoadingScreenRenderer {
public:
    LoadingScreenRenderer(Window* window);
    void render();

private:
    Window* window;
};
