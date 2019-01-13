#pragma once

#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Primitives.h"
#include "ObjLoader.h"

class Mesh
{
private:
    ObjLoader _objLoader;
    Vertex* _vertexArray;
    unsigned _numberOfVertices;
    GLuint* _indexArray;
    unsigned _numberOfIndices;

    std::vector<glm::vec3> _positions;
    std::vector<glm::vec2> _texcoords;
    std::vector<glm::vec3> _normals;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;

    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _ModelMatrix;

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        // texcoord
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        // normal
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);

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
        std::string filename,
        glm::vec3 position = glm::vec3(0.f),
        glm::vec3 rotation = glm::vec3(0.f),
        glm::vec3 scale = glm::vec3(1.f)
    )
        : _position(position)
        , _rotation(rotation)
        , _scale(scale)
    {
        _objLoader.load(filename);

        // something something
    }

    //Mesh(
    //    Vertex* vertexArray,
    //    const unsigned& numberOfVertices,
    //    GLuint* indexArray,
    //    const unsigned& numberOfIndices,
    //    glm::vec3 position = glm::vec3(0.f),
    //    glm::vec3 rotation = glm::vec3(0.f),
    //    glm::vec3 scale = glm::vec3(1.f)
    //)
    //    : _position(position)
    //    , _rotation(rotation)
    //    , _scale(scale)
    //{
    //    _numberOfVertices = numberOfVertices;
    //    _numberOfIndices = numberOfIndices;

    //    _vertexArray = new Vertex[_numberOfVertices];
    //    for (size_t i = 0; i < numberOfVertices; i++)
    //    {
    //        _vertexArray[i] = vertexArray[i];
    //    }

    //    _indexArray = new GLuint[_numberOfIndices];
    //    for (size_t i = 0; i < numberOfIndices; i++)
    //    {
    //        _indexArray[i] = indexArray[i];
    //    }

    //    this->initVAO();
    //    this->updateModelMatrix();
    //}
    
    //Mesh(
    //    Primitive *primitive,
    //    glm::vec3 position = glm::vec3(0.f),
    //    glm::vec3 rotation = glm::vec3(0.f),
    //    glm::vec3 scale = glm::vec3(1.f)
    //)
    //    : _position(position)
    //    , _rotation(rotation)
    //    , _scale(scale)
    //{
    //    _numberOfVertices = primitive->getNumberOfVertices();
    //    _numberOfIndices = primitive->getNumberOfIndices();

    //    _vertexArray = new Vertex[_numberOfVertices];
    //    for (size_t i = 0; i < primitive->getNumberOfVertices(); i++)
    //    {
    //        _vertexArray[i] = primitive->getVertices()[i];
    //    }

    //    _indexArray = new GLuint[_numberOfIndices];
    //    for (size_t i = 0; i < primitive->getNumberOfIndices(); i++)
    //    {
    //        _indexArray[i] = primitive->getIndices()[i];
    //    }

    //    this->initVAO();
    //    this->updateModelMatrix();
    //}

    Mesh(const Mesh& other)
    {
        _position = other._position;
        _rotation = other._rotation;
        _scale = other._scale;

        _numberOfVertices = other._numberOfVertices;
        _numberOfIndices = other._numberOfIndices;

        //_vertexArray = new Vertex[_numberOfVertices];
        //for (size_t i = 0; i < _numberOfVertices; i++)
        //{
        //    _vertexArray[i] = other._vertexArray[i];
        //}

        _indexArray = new GLuint[_numberOfIndices];
        for (size_t i = 0; i < _numberOfIndices; i++)
        {
            _indexArray[i] = other._indexArray[i];
        }

        this->initVAO();
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

        delete[] _vertexArray;
        delete[] _indexArray;
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

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};
