#include "Game.h"

Game::Game(
    const char* title, 
    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
    const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable
)
    : _WINDOW_WIDTH(WINDOW_WIDTH), _WINDOW_HEIGHT(WINDOW_HEIGHT)
    , _GL_VERSION_MAJOR(GL_VERSION_MAJOR), _GL_VERSION_MINOR(GL_VERSION_MINOR)
{
    _window = nullptr;
    _frameBufferWidth = WINDOW_WIDTH;
    _frameBufferHeight = WINDOW_HEIGHT;

    _cameraPosition = glm::vec3(0.f, 0.f, 1.f);
    _worldUp = glm::vec3(0.f, 1.f, 0.f);
    _cameraFront = glm::vec3(0.f, 0.f, -1.f);
    _fov = 90.f;
    _nearPlane = 0.1f;
    _farPlane = 1000.f;

    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGLEW();
    this->initOpenGLOptions();
    this->initMatrices();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    this->initMeshes();
    this->initLights();
    this->initUniforms();
}

Game::~Game()
{
    glfwDestroyWindow(_window);
    glfwTerminate();

    for (size_t i = 0; i < _shaders.size(); i++)
    {
        delete _shaders[i];
    }

    for (size_t i = 0; i < _textures.size(); i++)
    {
        delete _textures[i];
    }

    for (size_t i = 0; i < _materials.size(); i++)
    {
        delete _materials[i];
    }

    for (size_t i = 0; i < _meshes.size(); i++)
    {
        delete _meshes[i];
    }

    for (size_t i = 0; i < _lights.size(); i++)
    {
        delete _lights[i];
    }
}

void Game::initGLFW()
{
    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "error::Game::initGLFW::init_failed" << std::endl;
        glfwTerminate();
    }
}

void Game::initWindow(const char* title, bool resizable)
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _GL_VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    _window = glfwCreateWindow(_WINDOW_WIDTH, _WINDOW_HEIGHT, title, NULL, NULL);
    if (_window == nullptr)
    {
        std::cout << "error::Game::initWindow::init_failed" << std::endl;
        glfwTerminate();
    }

    glfwGetFramebufferSize(_window, &_frameBufferWidth, &_frameBufferHeight);
    glfwSetFramebufferSizeCallback(_window, Game::frameBufferResizeCallback);

    glfwMakeContextCurrent(_window);
}

void Game::initGLEW()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error::Game::initGLEW::init_failed" << std::endl;
        glfwTerminate();
    }
}

void Game::initOpenGLOptions()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE); // don't draw what's not shown
    glCullFace(GL_BACK); // cull face is the back
    glFrontFace(GL_CCW); // the back is when vertices point counter clockwise

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Game::initMatrices()
{
    _ViewMatrix = glm::mat4(1.f);
    _ViewMatrix = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _worldUp);

    _ProjectionMatrix = glm::mat4(1.f);
    _ProjectionMatrix = glm::perspective(
        glm::radians(_fov),
        static_cast<float>(_frameBufferWidth) / _frameBufferHeight,
        _nearPlane,
        _farPlane
    );
}

void Game::initShaders()
{
    _shaders.push_back(new Shader(_GL_VERSION_MAJOR, _GL_VERSION_MINOR, "vertex_core.glsl", "fragment_core.glsl"));
}

void Game::initTextures()
{
    _textures.push_back(new Texture("images/test.png", GL_TEXTURE_2D, 0));
    _textures.push_back(new Texture("images/brick.png", GL_TEXTURE_2D, 1));
}

void Game::initMaterials()
{
    _materials.push_back(new Material (
        glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
        _textures[TEXTURE_TEST0]->getTextureUnit(), _textures[TEXTURE_BRICK1]->getTextureUnit())
    );
}

void Game::initMeshes()
{
    _meshes.push_back(new Mesh(
        &Quad(),
        glm::vec3(0.f),
        glm::vec3(0.f), 
        glm::vec3(1.f)
    ));
}

void Game::initLights()
{
    _lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms()
{
    _shaders[SHADER_CORE_PROGRAM]->setMat4fv(_ViewMatrix, "ViewMatrix");
    _shaders[SHADER_CORE_PROGRAM]->setMat4fv(_ProjectionMatrix, "ProjectionMatrix");

    _shaders[SHADER_CORE_PROGRAM]->setVec3f(*_lights[0], "lightPos0");
    _shaders[SHADER_CORE_PROGRAM]->setVec3f(_cameraPosition, "cameraPos");
}

int Game::getWindowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void Game::setWindowShouldClose()
{
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
}

void Game::update()
{
    glfwPollEvents();
}

void Game::render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _shaders[SHADER_CORE_PROGRAM]->set1i(_textures[TEXTURE_TEST0]->getTextureUnit(), "texture0");
    _shaders[SHADER_CORE_PROGRAM]->set1i(_textures[TEXTURE_BRICK1]->getTextureUnit(), "texture1");
    _materials[MATERIAL_1]->sendToShader(*_shaders[SHADER_CORE_PROGRAM]);

    glfwGetFramebufferSize(_window, &_frameBufferWidth, &_frameBufferHeight);
    _ProjectionMatrix = glm::mat4(1.f);
    _ProjectionMatrix = glm::perspective(
        glm::radians(_fov),
        static_cast<float>(_frameBufferWidth) / _frameBufferHeight,
        _nearPlane,
        _farPlane
    );
    _shaders[SHADER_CORE_PROGRAM]->setMat4fv(_ProjectionMatrix, "ProjectionMatrix");

    _shaders[SHADER_CORE_PROGRAM]->use();

    _textures[TEXTURE_TEST0]->bind();
    _textures[TEXTURE_BRICK1]->bind();

    _meshes[MESH_QUAD]->render(_shaders[SHADER_CORE_PROGRAM]);

    glfwSwapBuffers(_window);
    glFlush();

    glBindVertexArray(0);
    _shaders[SHADER_CORE_PROGRAM]->unuse();
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::frameBufferResizeCallback(GLFWwindow * window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbW);
}
