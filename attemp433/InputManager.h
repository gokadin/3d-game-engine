#pragma once

#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <memory>


#include "Scene.h"

enum keyStates
{
    KEY_RELEASED,
    KEY_PRESSED,
    KEY_DOWN,
    KEY_UP
};

class InputManager
{
public:
    InputManager();

    ~InputManager();

    void updateInput(std::unique_ptr<Scene>& scene, GLFWwindow* window);

    void updateKeyPressInput(std::unique_ptr<Scene>& scene, GLFWwindow* window);
    void updateKeyDownInput(std::unique_ptr<Scene>& scene, GLFWwindow* window);
    void updateKeyUpInput(std::unique_ptr<Scene>& scene, GLFWwindow* window);

    void onKeyPress(int key, std::function<void (std::unique_ptr<Scene>& scene)> func);
    void onKeyDown(int key, std::function<void (std::unique_ptr<Scene>& scene)> func);
    void onKeyUp(int key, std::function<void (std::unique_ptr<Scene>& scene)> func);

    void onMouseMove(std::function<void(std::unique_ptr<Scene>& scene, const double& offsetX, const double& offsetY)> func);

private:
    std::map<int, std::function<void (std::unique_ptr<Scene>& scene)>> _keyPressMapping;
    std::map<int, std::function<void (std::unique_ptr<Scene>& scene)>> _keyDownMapping;
    std::map<int, std::function<void (std::unique_ptr<Scene>& scene)>> _keyUpMapping;
    std::function<void (std::unique_ptr<Scene>& scene, const double& offsetX, const double& offsetY)> _mouseMoveMapping;

    std::map<int, int> _keyStates;

    double _lastMouseX;
    double _lastMouseY;
    double _mouseX;
    double _mouseY;
    double _mouseOffsetX;
    double _mouseOffsetY;
    bool _firstMouse;

    void updateMouseInput(std::unique_ptr<Scene>& scene, GLFWwindow* window);

    void updateKeyStates(GLFWwindow* window);
    void updateKeyState(GLFWwindow* window, int key);
};

