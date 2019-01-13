#pragma once

#include <glew.h>
#include <glfw3.h>

#include <vector>

#include "Vertex.h"

class Primitive
{
private:
    std::vector<Vertex> _vertices;
    std::vector<GLuint> _indices;

public:
    Primitive() { }

    virtual ~Primitive() { }

    void set(
        const Vertex* vertices, 
        const unsigned numberOfVertices,
        const GLuint* indices,
        const unsigned numberOfIndices
    )
    {
        for (size_t i = 0; i < numberOfVertices; i++)
        {
            _vertices.push_back(vertices[i]);
        }

        for (size_t i = 0; i < numberOfIndices; i++)
        {

            _indices.push_back(indices[i]);
        }
    }

    inline Vertex* getVertices() { return _vertices.data(); }

    inline GLuint* getIndices() { return _indices.data(); }
    
    inline const unsigned getNumberOfVertices() { return _vertices.size(); }

    inline const unsigned getNumberOfIndices() { return _indices.size(); }
};

class Pyramid : public Primitive
{
public:
    Pyramid()
        : Primitive()
    {
        Vertex vertices[] =
        {
            // triangle front
            Vertex(glm::vec3(0.f, 0.5f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(0.f, 0.f, 1.f)),
            Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
            Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),

            // triangle left
            Vertex(glm::vec3(0.f, 0.5f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(1.f, 0.f, 0.f)),
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
            Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),

            // triangle back
            Vertex(glm::vec3(0.f, 0.5f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(0.f, 0.f, -1.f)),
            Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f)),
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, -1.f)),

            // triangle right
            Vertex(glm::vec3(0.f, 0.5f, 0.f), glm::vec2(0.5f, 1.f), glm::vec3(1.f, 0.f, 0.f)),
            Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
            Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.f)),
        };
        unsigned int numberOfVertices = sizeof(vertices) / sizeof(Vertex);

        this->set(vertices, numberOfVertices, nullptr, 0);
    }
};
