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
    _frameBufferHeight = WINDOW_WIDTH;

    _dt = 0.0;
    _curTime = 0.0;
    _lastTime = glfwGetTime();
    _timer = _lastTime;
    _limitFps = 1.0 / 100.0;
    _updateCounter = 0;
    _frameCounter = 0;

    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGLEW();
    this->initOpenGLOptions();
}

Game::~Game()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Game::loadScene(const std::string rootDirectory)
{
    _scene = std::make_unique<Scene>(_window, _GL_VERSION_MAJOR, _GL_VERSION_MINOR, _WINDOW_WIDTH, _WINDOW_HEIGHT);

    _gameLoader.load(rootDirectory);

    for (auto&[name, model] : _gameLoader.getRegistry().getModels())
    {
       _scene->addModel(name, model);
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

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

int Game::getWindowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void Game::setWindowShouldClose()
{
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
}

void Game::updateDt()
{
    _curTime = glfwGetTime();
    _dt = _curTime - _lastTime;
    _lastTime = _curTime;
}

void Game::updateInput()
{
    _inputManager.updateInput(_scene, _window);
}

void Game::update()
{
    this->updateDt();
    this->updateInput();

    _scene->update(_dt);

    _updateCounter++;

    if (glfwGetTime() - _timer > 1.0)
    {
        //std::cout << "FPS: " << _frameCounter << " UPS: " << _updateCounter << std::endl;

        _timer++;
        _updateCounter = 0;
        _frameCounter = 0;
    }
}

void Game::render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _scene->render();

    _frameCounter++;

    glfwSwapBuffers(_window);
    glFlush();
}

void Game::frameBufferResizeCallback(GLFWwindow * window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbW);
}
