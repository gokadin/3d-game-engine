#pragma once

#include "MeshMaterial.h"
#include "Vertex.h"
#include "Shader.h"

class SubMesh
{
private:
    Vertex* _vertexArray;
    unsigned _numberOfVertices;
    GLuint* _indexArray;
    unsigned _numberOfIndices;

    GLenum _polygonMode;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;

    std::shared_ptr<MeshMaterial> _material;

    void initVAO()
    {
        glCreateVertexArrays(1, &this->_VAO);
        glBindVertexArray(this->_VAO);

        glGenBuffers(1, &this->_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
        glBufferData(GL_ARRAY_BUFFER, this->_numberOfVertices * sizeof(Vertex), _vertexArray, GL_STATIC_DRAW); // GL_STATIC_DRAW if not changing much ortherwise GL_DYNAMIC_DRAW

        glGenBuffers(1, &this->_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_numberOfIndices * sizeof(GLuint), _indexArray, GL_STATIC_DRAW);

        // input assembly (how we tell the shader what each float is in our buffer)
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        // texcoord
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(1);

        // normal
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

public:
    SubMesh(const std::shared_ptr<MeshMaterial>& material, std::vector<Vertex> vertices)
        : _material(material), _polygonMode(GL_FILL)
    {

        _numberOfVertices = vertices.size();

        _vertexArray = new Vertex[_numberOfVertices];
        for (size_t i = 0; i < _numberOfVertices; i++)
        {
            _vertexArray[i] = vertices[i];
        }

        _numberOfIndices = 0;
        _indexArray = nullptr;

        this->initVAO();
    }

    ~SubMesh()
    {
        glDeleteVertexArrays(1, &this->_VAO);
        glDeleteBuffers(1, &this->_VBO);

        if (_numberOfIndices > 0)
        {
            glDeleteBuffers(1, &this->_EBO);
        }

        delete[] _vertexArray;

        if (_indexArray != nullptr)
        {
            delete[] _indexArray;
        }
    }

    unsigned getNumberOfVertices() { return _numberOfVertices; }

    Vertex* getVertices() { return _vertexArray; }

    inline void setPolygonMode(GLenum mode) { _polygonMode = mode; }

    void render(Shader* shader)
    {
        _material->bind(*shader);
        glBindVertexArray(this->_VAO);
        shader->use();

        if (_polygonMode != GL_FILL)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        if (_numberOfIndices <= 0)
        {
            glDrawArrays(GL_TRIANGLES, 0, _numberOfVertices);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, this->_numberOfIndices, GL_UNSIGNED_INT, 0);
        }

        if (_polygonMode != GL_FILL)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        _material->unbind();
        glBindVertexArray(0);
        glUseProgram(0);
    }
};
