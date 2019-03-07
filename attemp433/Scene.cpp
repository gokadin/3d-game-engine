#include "Scene.h"

Scene::Scene(
        GLFWwindow* window,
        int GL_VERSION_MAJOR, int GL_VERSION_MINOR,
        const int WINDOW_WIDTH, const int WINDOW_HEIGHT
)
    : _window(window)
    , _GL_VERSION_MAJOR(GL_VERSION_MAJOR), _GL_VERSION_MINOR(GL_VERSION_MINOR)
    , _camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
    _frameBufferWidth = WINDOW_WIDTH;
    _frameBufferHeight = WINDOW_HEIGHT;

    _fov = 60.f;
    _nearPlane = 0.1f;
    _farPlane = 1000.f;

    this->initShaders();
    this->initLights();
    this->initUniforms();
    this->initMatrices();
}

Scene::~Scene()
{
    for (size_t i = 0; i < _shaders.size(); i++)
    {
        delete _shaders[i];
    }

    for (size_t i = 0; i < _lights.size(); i++)
    {
        delete _lights[i];
    }
}

void Scene::initShaders()
{
    _shaders.push_back(new Shader(_GL_VERSION_MAJOR, _GL_VERSION_MINOR, "vertex_core.glsl", "fragment_core.glsl"));
}

void Scene::initLights()
{
    _lights.push_back(new glm::vec3(0.f, 4.f, -2.f));
}

void Scene::initUniforms()
{
    _shaders[SHADER_CORE_PROGRAM]->setMat4fv(_camera.getViewMatrix(), "ViewMatrix");
    _shaders[SHADER_CORE_PROGRAM]->setMat4fv(_ProjectionMatrix, "ProjectionMatrix");

    _shaders[SHADER_CORE_PROGRAM]->setVec3f(*_lights[0], "lightPos0");
}

void Scene::initMatrices()
{
    _ProjectionMatrix = glm::mat4(1.f);
    _ProjectionMatrix = glm::perspective(
        glm::radians(_fov),
        static_cast<float>(_frameBufferWidth) / _frameBufferHeight,
        _nearPlane,
        _farPlane
    );
}

void Scene::closeWindow()
{
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
}

void Scene::updateUniforms()
{
    _shaders[SHADER_CORE_PROGRAM]->setMat4fv(_camera.getViewMatrix(), "ViewMatrix");
    _shaders[SHADER_CORE_PROGRAM]->setVec3f(_camera.getPosition(), "cameraPos");

    glfwGetFramebufferSize(_window, &_frameBufferWidth, &_frameBufferHeight);

    _ProjectionMatrix = glm::perspective(
        glm::radians(_fov),
        static_cast<float>(_frameBufferWidth) / _frameBufferHeight,
        _nearPlane,
        _farPlane
    );
    _shaders[SHADER_CORE_PROGRAM]->setMat4fv(_ProjectionMatrix, "ProjectionMatrix");
}

void Scene::update(const double& dt)
{
    _physicsEngine.update(_world.getPhysics(), _models, dt);

    _collisionManager.updateCollisions(_models);

    for (auto& [name, model] : _models)
    {
        model->update();
    }
}

void Scene::render()
{
    this->updateUniforms();

    for (auto& [name, model] : _models)
    {
        model->render(_shaders[SHADER_CORE_PROGRAM]);
    }
}
