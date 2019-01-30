#pragma once

#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>

#include "enums.h"

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
        _front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front.y = sin(glm::radians(_pitch));
        _front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

        _front = glm::normalize(_front);
        _right = glm::normalize(glm::cross(_front, _worldUp));
        _up = glm::normalize(glm::cross(_right, _front));
    }

public:
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
        : _position(position), _worldUp(worldUp)
        , _movementSpeed(1.f), _sensitivity(0.1f)
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

    void move(const int direction)
    {
        switch (direction)
        {
        case AT_CAMERA_DIRECTION_FORWARD:
            _position += _front * _movementSpeed;
            break;
        case AT_CAMERA_DIRECTION_BACKWARD:
            _position -= _front * _movementSpeed;
            break;
        case AT_CAMERA_DIRECTION_LEFT:
            _position -= _right * _movementSpeed;
            break;
        case AT_CAMERA_DIRECTION_RIGHT:
            _position += _right * _movementSpeed;
            break;
        default:
            break;
        }
    }

    void updateMouseInput(const double& offsetX, const double& offsetY)
    {
        _pitch -= static_cast<GLfloat>(offsetY) * _sensitivity;
        _yaw += static_cast<GLfloat>(offsetX) * _sensitivity;

        if (_pitch > 80.f)
            _pitch = 80.f;
        else if (_pitch < -80.f)
            _pitch = -80.f;

        if (_yaw > 360.f || _yaw < -360.f)
            _yaw = 0.f;
    }
};
