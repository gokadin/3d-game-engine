#pragma once

#include "libs.h"

enum shaderEnum
{
    SHADER_CORE_PROGRAM = 0
};

enum textureEnum
{
    TEXTURE_TEST0 = 0,
    TEXTURE_BRICK1
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
    GLFWwindow* _window;
    const int _WINDOW_WIDTH;
    const int _WINDOW_HEIGHT;
    const int _GL_VERSION_MAJOR;
    const int _GL_VERSION_MINOR;
    int _frameBufferWidth;
    int _frameBufferHeight;

    glm::mat4 _ViewMatrix;
    glm::vec3 _cameraPosition;
    glm::vec3 _worldUp;
    glm::vec3 _cameraFront;
    glm::mat4 _ProjectionMatrix;
    float _fov;
    float _nearPlane;
    float _farPlane;

    std::vector<Shader*> _shaders;
    std::vector<Texture*> _textures;
    std::vector<Material*> _materials;
    std::vector<Mesh*> _meshes;
    std::vector<glm::vec3*> _lights;

    void initGLFW();
    void initWindow(const char* title, bool resizable);
    void initGLEW();
    void initOpenGLOptions();
    void initMatrices();
    void initShaders();
    void initTextures();
    void initMaterials();
    void initMeshes();
    void initLights();
    void initUniforms();

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

    void update();

    void render();

    static void frameBufferResizeCallback(GLFWwindow* window, int fbW, int fbH);
};
