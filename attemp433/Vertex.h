#pragma once

#include <glm.hpp>

struct Vertex
{
private:
    glm::vec3 _position;
    glm::vec2 _texcoord;
    glm::vec3 _normal;

public:
    Vertex(glm::vec3 position,  glm::vec2 texcoord, glm::vec3 normal)
        : _position(position), _texcoord(texcoord), _normal(normal) { }

    glm::vec3 getPosition() { return _position; }

    glm::vec2 getTexcoord() { return _texcoord; }

    glm::vec3 getNormal() { return _normal; }
};
