#pragma once

#include <glm.hpp>
#include <vec3.hpp>

class BoundingBox
{
public:
    void initialize(glm::vec3 position, glm::vec3 size)
    {
        _position = position;
        _size = size;

        _nextPosition = glm::vec3(0.f);

    //std::vector<Vertex> vertices;
    //Vertex v1, v2, v3, v4, v5, v6;
    //v1.position = glm::vec3(_minX, _maxY, _maxZ); // left far
    //v2.position = glm::vec3(_maxX, _maxY, _minZ); // right close
    //v3.position = glm::vec3(_minX, _maxY, _minZ); // left close
    //v4.position = glm::vec3(_minX, _maxY, _maxZ); // left far
    //v5.position = glm::vec3(_maxX, _maxY, _maxZ); // right far
    //v6.position = glm::vec3(_maxX, _maxY, _minZ); // right close
    //vertices.push_back(v1);
    //vertices.push_back(v2);
    //vertices.push_back(v3);
    //vertices.push_back(v4);
    //vertices.push_back(v5);
    //vertices.push_back(v6);

    //std::shared_ptr<MeshMaterial> debugMaterial = std::make_shared<MeshMaterial>("debug");
    //debugMaterial->setAmbientColor(glm::vec3(1.f, 0.5f, 0.5f));
    //debugMaterial->setDiffuseColor(glm::vec3(0.7f, 0.5f, 1.f));

    //_debugSubMesh = std::make_unique<SubMesh>(debugMaterial, vertices);
    //_debugSubMesh->setPolygonMode(GL_LINE);
    }

    void move(glm::vec3 position)
    {
        _nextPosition = position;
    }

    bool isColliding(const BoundingBox& other) const
    {
        return (_position.x + _size.x / 2 >= other._position.x - other._size.x / 2
            && _position.x - _size.x / 2 <= other._position.x + other._size.x / 2)
            &&
            (_position.y + _size.y / 2 >= other._position.y - other._size.y / 2
                && _position.y - _size.y / 2 <= other._position.y + other._size.y / 2)
            &&
            (_position.z + _size.z / 2 >= other._position.z - other._size.z / 2
                && _position.z - _size.z / 2 <= other._position.z + other._size.z / 2);
    }

    void update()
    {
        this->commit();
    }

private:
    glm::vec3 _position;
    glm::vec3 _nextPosition;
    glm::vec3 _size;

    void commit()
    {
        _position += _nextPosition;
        _nextPosition = glm::vec3(0.f);
    }
};
