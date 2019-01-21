#pragma once

#include "libs.h"
#include "Camera.h"
#include "WorldPhysics.h"
#include "CollisionManager.h"

enum shaderEnum
{
    SHADER_CORE_PROGRAM = 0
};

enum textureEnum
{
    TEXTURE_TEST = 0,
    TEXTURE_TEST_SPECULAR,
    TEXTURE_BRICK,
    TEXTURE_BRICK_SPECULAR
};

enum materialEnum
{
    MATERIAL_1 = 0
};

enum meshEnum
{
    MESH_QUAD = 0
};

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

    // matrices
    glm::vec3 _worldUp;
    glm::vec3 _cameraFront;
    glm::mat4 _ProjectionMatrix;
    float _fov;
    float _nearPlane;
    float _farPlane;

    // delta time
    float _dt;
    float _curTime;
    float _lastTime;

    // mouse input
    double _lastMouseX;
    double _lastMouseY;
    double _mouseX;
    double _mouseY;
    double _mouseOffsetX;
    double _mouseOffsetY;
    bool _firstMouse;

    // camera
    Camera _camera;

    std::vector<Shader*> _shaders;

    std::vector<std::shared_ptr<Model>> _models;

    std::vector<glm::vec3*> _lights;

    WorldPhysics _physics;

    CollisionManager _collisionManager;

    void initGLFW();
    void initWindow(const char* title, bool resizable);
    void initGLEW();
    void initOpenGLOptions();
    void initMatrices();
    void initShaders();
    void initLights();
    void initUniforms();

    void updateUniforms();

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

    void updateDt();

    void updateKeyboardInput();

    void updateMouseInput();

    void updateInput();

    void update();

    void render();

    // setup

    void addModel(std::shared_ptr<Model>& model)
    {
        _models.push_back(model);
    }

    inline WorldPhysics& getPhysics() { return _physics; }

    // static

    static void frameBufferResizeCallback(GLFWwindow* window, int fbW, int fbH);
};

