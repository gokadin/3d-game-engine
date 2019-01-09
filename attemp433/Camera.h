#pragma once

#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>

class Camera
{
private:
    glm::mat4 _ViewMatrix;

    GLfloat _movementSpeed;
    GLfloat _sensitivity;

    glm::vec3 _worldUp;
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _right;
    glm::vec3 _up;

    GLfloat _pitch;
    GLfloat _yaw;
    GLfloat _roll;

    void updateCameraVectors()
    {

    }

public:
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
        : _position(position), _worldUp(worldUp)
    {

    }

    ~Camera() {}

    const glm::mat4 getViewMatrix()
    {
        this->updateCameraVectors();

        _ViewMatrix = glm::lookAt(_position, _position + _front, _up);

        return _ViewMatrix;
    }

    const glm::vec3 getPosition() const
    {
        return _position;
    }

    void updateKeyboardInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
    {

    }

    void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
    {

    }

    void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
    {
        this->updateMouseInput(dt, offsetX, offsetY);
        this->updateKeyboardInput(dt, direction, offsetX, offsetY);
    }
};
