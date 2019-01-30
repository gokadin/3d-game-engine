#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <glm.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"
#include "CollisionManager.h"
#include "physics/PhysicsEngine.h"
#include "World.h"
#include "Model.h"

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

class Scene
{
public:
    Scene(
        GLFWwindow* window,
        int GL_VERSION_MAJOR, int GL_VERSION_MINOR,
        const int WINDOW_WIDTH, const int WINDOW_HEIGHT
    );

    ~Scene();

    void closeWindow();

    void addModel(const std::string& name, std::shared_ptr<Model>& model)
    {
        _models[name] = model;
    }

    inline World& getWorld() { return _world; }

    std::shared_ptr<Model>& getModel(const std::string& name) { return _models[name]; }

    inline Camera& getCamera() { return _camera; }

    void update(const double& dt);

    void render();

private:
    GLFWwindow* _window;
    const int _GL_VERSION_MAJOR;
    const int _GL_VERSION_MINOR;
    int _frameBufferWidth;
    int _frameBufferHeight;

    Camera _camera;
    glm::vec3 _worldUp;
    glm::vec3 _cameraFront;
    glm::mat4 _ProjectionMatrix;
    float _fov;
    float _nearPlane;
    float _farPlane;

    std::vector<Shader*> _shaders;

    std::map<std::string, std::shared_ptr<Model>> _models;

    std::vector<glm::vec3*> _lights;

    CollisionManager _collisionManager;

    PhysicsEngine _physicsEngine;

    World _world;

    void initShaders();
    void initLights();
    void initUniforms();
    void initMatrices();

    void updateUniforms();
};

