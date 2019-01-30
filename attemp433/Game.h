#pragma once

#include <map>

#include "Scene.h"
#include "loader/GameLoader.h"
#include "InputManager.h"

class Game
{
private:
    // window
    GLFWwindow* _window;
    const int _WINDOW_WIDTH;
    const int _WINDOW_HEIGHT;
    const int _GL_VERSION_MAJOR;
    const int _GL_VERSION_MINOR;
    int _frameBufferWidth;
    int _frameBufferHeight;

    // delta time
    double _dt;
    double _curTime;
    double _lastTime;
    double _timer;
    double _limitFps;
    int _updateCounter;
    int _frameCounter;

    InputManager _inputManager;

    GameLoader _gameLoader;

    std::unique_ptr<Scene> _scene;

    void initGLFW();
    void initWindow(const char* title, bool resizable);
    void initGLEW();
    void initOpenGLOptions();

public:
    Game(
        const char* title, 
        const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
        int GL_VERSION_MAJOR, int GL_VERSION_MINOR,
        bool resizable
    );

    virtual ~Game();

    int getWindowShouldClose();

    void setWindowShouldClose();

    void loadScene(const std::string rootDirectory);

    void updateDt();

    void updateInput();

    void update();

    void render();

    inline InputManager& getInputManager() { return _inputManager; }

    inline std::unique_ptr<Scene>& getScene() { return _scene; }

    // static

    static void frameBufferResizeCallback(GLFWwindow* window, int fbW, int fbH);
};

