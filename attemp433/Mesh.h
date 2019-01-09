#pragma once

#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Primitives.h"

class Mesh
{
private:
    unsigned _numberOfVertices;
    unsigned _numberOfIndices;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;

    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _ModelMatrix;

    void initVAO(Primitive *primitive)
    {
        this->_numberOfVertices = primitive->getNumberOfVertices();
        this->_numberOfIndices = primitive->getNumberOfIndices();

        glCreateVertexArrays(1, &this->_VAO);
        glBindVertexArray(this->_VAO);

        glGenBuffers(1, &this->_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
        glBufferData(GL_ARRAY_BUFFER, this->_numberOfVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW); // GL_STATIC_DRAW if not changing much ortherwise GL_DYNAMIC_DRAW

        glGenBuffers(1, &this->_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_numberOfIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);

        // input assembly (how we tell the shader what each float is in our buffer)
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        // texcoord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(2);

        // normal
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);
    }

    void initVAO(
        Vertex* vertexArray,
        const unsigned& numberOfVertices,
        GLuint* indexArray,
        const unsigned& numberOfIndices
    )
    {
        this->_numberOfVertices = numberOfVertices;
        this->_numberOfIndices = numberOfIndices;

        glCreateVertexArrays(1, &this->_VAO);
        glBindVertexArray(this->_VAO);

        glGenBuffers(1, &this->_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
        glBufferData(GL_ARRAY_BUFFER, this->_numberOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW); // GL_STATIC_DRAW if not changing much ortherwise GL_DYNAMIC_DRAW

        glGenBuffers(1, &this->_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_numberOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

        // input assembly (how we tell the shader what each float is in our buffer)
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        // texcoord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(2);

        // normal
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);
    }

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
        Vertex* vertexArray,
        const unsigned& numberOfVertices,
        GLuint* indexArray,
        const unsigned& numberOfIndices,
        glm::vec3 position = glm::vec3(0.f),
        glm::vec3 rotation = glm::vec3(0.f),
        glm::vec3 scale = glm::vec3(1.f)
    )
        : _position(position)
        , _rotation(rotation)
        , _scale(scale)
    {
        this->_position = glm::vec3(0.f);
        this->_rotation = glm::vec3(0.f);
        this->_scale = glm::vec4(1.f);

        this->initVAO(vertexArray, numberOfVertices, indexArray, numberOfIndices);
        this->updateModelMatrix();
    }
    
    Mesh(
        Primitive *primitive,
        glm::vec3 position = glm::vec3(0.f),
        glm::vec3 rotation = glm::vec3(0.f),
        glm::vec3 scale = glm::vec3(1.f)
    )
        : _position(position)
        , _rotation(rotation)
        , _scale(scale)
    {
        this->_position = glm::vec3(0.f);
        this->_rotation = glm::vec3(0.f);
        this->_scale = glm::vec4(1.f);

        this->initVAO(primitive);
        this->updateModelMatrix();
    }

    ~Mesh()
    {
        glDeleteVertexArrays(1, &this->_VAO);
        glDeleteBuffers(1, &this->_VBO);

        if (_numberOfIndices > 0)
        {
            glDeleteBuffers(1, &this->_EBO);
        }
    }

    void setPosition(const glm::vec3 position) { this->_position = position; }

    void setRotation(const glm::vec3 rotation) { this->_rotation = rotation; }

    void setScale(const glm::vec3 scale) { this->_scale = scale; }

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

    void update()
    {

    }

    void render(Shader* shader)
    {
        this->updateModelMatrix();
        this->updateUniforms(shader);

        shader->use();

        glBindVertexArray(this->_VAO);

        if (_numberOfIndices <= 0)
        {
            glDrawArrays(GL_TRIANGLES, 0, _numberOfVertices);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, this->_numberOfIndices, GL_UNSIGNED_INT, 0);
        }
    }
};
