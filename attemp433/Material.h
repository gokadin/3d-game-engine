#pragma once

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

class Material
{
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    std::vector<Texture*> _textures;

public:
    Material(
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular
    )
        : ambient(ambient)
        , diffuse(diffuse)
        , specular(specular)
    {

    }

    ~Material()
    { 
        for (size_t i = 0; i < _textures.size(); i++)
        {
            delete _textures[i];
        }
    }


    void add2DTexture(std::string filename, GLenum type)
    {
        _textures.push_back(new Texture(filename, type));
    }

    void bind(Shader& shader)
    {
        shader.setVec3f(this->ambient, "material.ambient");
        shader.setVec3f(this->diffuse, "material.diffuse");
        shader.setVec3f(this->specular, "material.specular");
        shader.set1i(0, "material.diffuseTex");
        shader.set1i(1, "material.specularTex");

        for (size_t i = 0; i < _textures.size(); i++)
        {
            _textures[i]->bind(i);
        }
    }

    void unbind()
    {
        for (size_t i = 0; i < _textures.size(); i++)
        {
            _textures[i]->unbind();
        }
    }
};
