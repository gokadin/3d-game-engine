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

class Quad : public Primitive
{
public:
    Quad()
        : Primitive()
    {
        Vertex vertices[] =
        {
            // position                     // color                    // texture              // normal
            glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),  glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(-0.5f, -0.5f, 0.f),    glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),   glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(1.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, 0.5f, 0.f),    glm::vec3(0.f, 1.f, 1.f),   glm::vec2(1.f, 1.f),    glm::vec3(0.f, 0.f, 1.f)
        };
        unsigned int numberOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] = 
        {
            0, 1, 2, 3, 0, 2
        };
        unsigned int numberOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, numberOfVertices, indices, numberOfIndices);
    }
};

class Triangle : public Primitive
{
public:
    Triangle()
        : Primitive()
    {
        Vertex vertices[] =
        {
            // position                     // color                    // texture              // normal
            glm::vec3(0.f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),  glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(-0.5f, -0.5f, 0.f),    glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),   glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(1.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
        };
        unsigned int numberOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] = 
        {
            0, 1, 2
        };
        unsigned int numberOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, numberOfVertices, indices, numberOfIndices);
    }
};
