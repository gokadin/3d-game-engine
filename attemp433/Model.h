#pragma once

#include <iostream>
#include <vector>
#include <glm.hpp>
#include <vec3.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "ItemPhysics.h"

class Model
{
private:
    std::string _name;
    glm::vec3 _size;
    glm::vec3 _position;
    glm::vec3 _velocity;

    std::vector<std::shared_ptr<Mesh>> _meshes;

    ItemPhysics _physics;

    // up is clean

    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _ModelMatrix;

    void updateUniforms(Shader* shader)
    {
        shader->setMat4fv(this->_ModelMatrix, "ModelMatrix");
    }

    void updateModelMatrix()
    {
        this->_ModelMatrix = glm::mat4(1.f);
        this->_ModelMatrix = glm::translate(this->_ModelMatrix, this->_position);
        this->_ModelMatrix = glm::rotate(this->_ModelMatrix, glm::radians(this->_rotation.x), glm::vec3(1.f, 0.f, 0.f));
        this->_ModelMatrix = glm::rotate(this->_ModelMatrix, glm::radians(this->_rotation.y), glm::vec3(0.f, 1.f, 0.f));
        this->_ModelMatrix = glm::rotate(this->_ModelMatrix, glm::radians(this->_rotation.z), glm::vec3(0.f, 0.f, 1.f));
        this->_ModelMatrix = glm::scale(this->_ModelMatrix, this->_scale);
    }

public:
    Model(
        glm::vec3 position = glm::vec3(0.f),
        glm::vec3 rotation = glm::vec3(0.f),
        glm::vec3 scale = glm::vec3(1.f)
    );

    ~Model();

    inline const std::string& getName() const { return _name; }
    inline const glm::vec3& getSize() const { return _size; }

    inline void setName(const std::string name) { _name = name; }
    inline void setSize(const glm::vec3 size) { _size = size; }
    inline void setPosition(const glm::vec3 position) { this->_position = position; }
    inline void setRotation(const glm::vec3 rotation) { this->_rotation = rotation; }
    inline void setScale(const glm::vec3 scale) { this->_scale = scale; }

    inline void setVelocity(const glm::vec3 velocity) { this->_velocity = velocity; }
    inline void addVelocity(const glm::vec3 velocity) { this->_velocity += velocity; }

    void addMesh(const std::shared_ptr<Mesh>& mesh)
    {
        _meshes.push_back(mesh);
    }

    // up is clean

    void rotate(const glm::vec3 rotation)
    {
        this->_rotation += rotation;
    }

    void scale(const glm::vec3 scale)
    {
        this->_scale += scale;
    }

    // ...

    inline ItemPhysics& getPhysics() { return _physics; }

    inline const glm::vec3& getPosition() { return _position; }

    void update();

    void render(Shader* shader);
};

