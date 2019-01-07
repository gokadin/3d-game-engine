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

class Material
{
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLint diffuseTex;
    GLint specularTex;

public:
    Material(
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        GLint diffuseTex,
        GLint specularTex
    )
        : ambient(ambient)
        , diffuse(diffuse)
        , specular(specular)
        , diffuseTex(diffuseTex)
        , specularTex(specularTex)
    {

    }

    ~Material() { }

    void sendToShader(Shader& shader)
    {
        shader.setVec3f(this->ambient, "material.ambient");
        shader.setVec3f(this->diffuse, "material.diffuse");
        shader.setVec3f(this->specular, "material.specular");
        shader.set1i(diffuseTex, "material.diffuseTex");
        shader.set1i(specularTex, "material.specularTex");
    }
};
