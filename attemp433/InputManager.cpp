#include "InputManager.h"

InputManager::InputManager()
{
    _lastMouseX = 0.0;
    _lastMouseY = 0.0;
    _mouseX = 0.0;
    _mouseY = 0.0;
    _mouseOffsetX = 0.0;
    _mouseOffsetY = 0.0;
    _firstMouse = true;
}

InputManager::~InputManager()
{
}

void InputManager::updateInput(std::unique_ptr<Scene>& scene, GLFWwindow* window)
{
    glfwPollEvents();

    this->updateKeyStates(window);

    this->updateKeyDownInput(scene, window);
    this->updateKeyPressInput(scene, window);
    this->updateKeyUpInput(scene, window);

    this->updateMouseInput(scene, window);
}

void InputManager::updateKeyPressInput(std::unique_ptr<Scene>& scene, GLFWwindow * window)
{
    for (auto&[key, callback] : _keyPressMapping)
    {
        if (_keyStates[key] == KEY_PRESSED || _keyStates[key] == KEY_DOWN)
        {
           callback(scene);
        }
    }
}

void InputManager::updateKeyDownInput(std::unique_ptr<Scene>& scene, GLFWwindow * window)
{
    for (auto&[key, callback] : _keyDownMapping)
    {
        if (_keyStates[key] == KEY_DOWN)
        {
            callback(scene);
        }
    }
}

void InputManager::updateKeyUpInput(std::unique_ptr<Scene>& scene, GLFWwindow * window)
{
    for (auto&[key, callback] : _keyUpMapping)
    {
        if (_keyStates[key] == KEY_UP)
        {
            callback(scene);
        }
    }
}

void InputManager::onKeyPress(int key, std::function<void(std::unique_ptr<Scene>& scene)> func)
{
    _keyPressMapping[key] = func;
    _keyStates[key] = KEY_RELEASED;
}

void InputManager::onKeyDown(int key, std::function<void(std::unique_ptr<Scene>&scene)> func)
{
    _keyDownMapping[key] = func;
    _keyStates[key] = KEY_RELEASED;
}

void InputManager::onKeyUp(int key, std::function<void(std::unique_ptr<Scene>&scene)> func)
{
    _keyUpMapping[key] = func;
    _keyStates[key] = KEY_RELEASED;
}

void InputManager::onMouseMove(std::function<void(std::unique_ptr<Scene>&scene, const double&offsetX, const double&offsetY)> func)
{
    _mouseMoveMapping = func;
}

void InputManager::updateMouseInput(std::unique_ptr<Scene>& scene, GLFWwindow * window)
{
    glfwGetCursorPos(window, &_mouseX, &_mouseY);

    if (_firstMouse)
    {
        _lastMouseX = _mouseX;
        _lastMouseY = _mouseY;
        _firstMouse = false;
    }

    _mouseOffsetX = _mouseX - _lastMouseX;
    _mouseOffsetY = _mouseY - _lastMouseY;

    _lastMouseX = _mouseX;
    _lastMouseY = _mouseY;

    if (_mouseMoveMapping != nullptr)
    {
        _mouseMoveMapping(scene, _mouseOffsetX, _mouseOffsetY);
    }
}

void InputManager::updateKeyStates(GLFWwindow* window)
{
    for (auto&[key, state] : _keyStates)
    {
        this->updateKeyState(window, key);
    }
}

void InputManager::updateKeyState(GLFWwindow* window, int key)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
        if (_keyStates[key] == KEY_RELEASED)
        {
            _keyStates[key] = KEY_DOWN;
        }
        else if (_keyStates[key] == KEY_DOWN)
        {
            _keyStates[key] = KEY_PRESSED;
        }
    }
    else
    {
        if (_keyStates[key] == KEY_PRESSED)
        {
            _keyStates[key] = KEY_UP;
        }
        else if (_keyStates[key] == KEY_UP)
        {
            _keyStates[key] = KEY_RELEASED;
        }
    }
}
