#pragma once

#include <iostream>
#include <vector>

#include "Shader.h"
#include "SubMesh.h"
#include "ItemPhysics.h"
#include "ObjLoader.h"

class Mesh
{
private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    std::vector<std::shared_ptr<SubMesh>> _subMeshes;

    glm::mat4 _ModelMatrix;

    uint32_t _id;
    //glm::vec3 _position;
    glm::vec3 _displacement;
    ItemPhysics _physics;

    ObjLoader _objLoader;

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
    Mesh(
        glm::vec3 position = glm::vec3(0.f),
        glm::vec3 rotation = glm::vec3(0.f),
        glm::vec3 scale = glm::vec3(1.f)
    );

    ~Mesh();

    void addSubMesh(const std::shared_ptr<SubMesh>& subMesh)
    {
        _subMeshes.push_back(subMesh);
    }

    void setPosition(const glm::vec3 position) { this->_position = position; }

    void setRotation(const glm::vec3 rotation) { this->_rotation = rotation; }

    void setScale(const glm::vec3 scale) { this->_scale = scale; }

    const std::vector<std::shared_ptr<SubMesh>>& getSubMeshes() { return _subMeshes; }

    void move(const glm::vec3 position)
    {
        this->_position += position;
    }

    void rotate(const glm::vec3 rotation)
    {
        this->_rotation += rotation;
    }

    void scale(const glm::vec3 scale)
    {
        this->_scale += scale;
    }

    void render(Shader* shader)
    {
        this->updateModelMatrix();
        this->updateUniforms(shader);

        for (size_t i = 0; i < _subMeshes.size(); i++)
        {
            _subMeshes[i]->render(shader);
        }
    }

    // ...

    inline const uint32_t getId() { return _id; }

    inline ItemPhysics& getPhysics() { return _physics; }

    void load(std::string filename);

    inline const glm::vec3& getPosition() { return _position; }

    void setDisplacement(const glm::vec3 displacement);

    void move(const glm::vec3 displacement);

    const glm::vec3& getFuturePosition();

    void update();

    void render(Shader* shader);

    void commit();
};

