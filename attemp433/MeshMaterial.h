#pragma once

#include <string>

#include <glm.hpp>
#include <vec3.hpp>

#include "Texture.h"
#include "Shader.h"

class MeshMaterial
{
public:
    MeshMaterial(std::string name)
        : _name(name)
        , _ambientColor(glm::vec3(0.f))
        , _diffuseColor(glm::vec3(0.f))
        , _specularColor(glm::vec3(0.f))
        , _specularExponent(0) { }

    ~MeshMaterial()
    {

    }

    inline std::string& getName() { return _name; }
    inline glm::vec3& getAmbientColor() { return _ambientColor; }
    inline glm::vec3& getDiffuseColor() { return _diffuseColor; }
    inline glm::vec3& getSpecularColor() { return _specularColor; }
    inline int getSpecularExponent() { return _specularExponent; }
    inline std::unique_ptr<Texture>& getAmbientTexture() { return _ambientTexture; }
    inline std::unique_ptr<Texture>& getDiffuseTexture() { return _diffuseTexture; }
    inline std::unique_ptr<Texture>& getSpecularTexture() { return _specularTexture; }

    inline void setAmbientColor(glm::vec3 ambientColor) { _ambientColor = ambientColor; }
    inline void setDiffuseColor(glm::vec3 diffuseColor) { _diffuseColor = diffuseColor; }
    inline void setSpecularColor(glm::vec3 specularColor) { _specularColor = specularColor; }
    inline void setSpecularExponent(int specularExponent) { _specularExponent = specularExponent; }

    void addAmbientTexture(std::string filename)
    {
        _ambientTexture = std::make_unique<Texture>(filename, GL_TEXTURE_2D);
    }

    void addDiffuseTexture(std::string filename)
    {
        _diffuseTexture = std::make_unique<Texture>(filename, GL_TEXTURE_2D);
    }

    void addSpecularTexture(std::string filename)
    {
        _specularTexture = std::make_unique<Texture>(filename, GL_TEXTURE_2D);
    }

    void bind(Shader& shader)
    {
        shader.setVec3f(_ambientColor, "material.ambient");
        shader.setVec3f(_diffuseColor, "material.diffuse");
        shader.setVec3f(_specularColor, "material.specular");
        shader.set1i(0, "material.ambientTex");
        shader.set1i(1, "material.diffuseTex");
        shader.set1i(2, "material.specularTex");
        shader.setBool(_ambientTexture != nullptr, "material.useAmbientTexture");
        shader.setBool(_diffuseTexture != nullptr, "material.useDiffuseTexture");
        shader.setBool(_specularTexture != nullptr, "material.useSpecularTexture");

        if (_ambientTexture != nullptr)
        {
            _ambientTexture->bind(0);
        }

        if (_diffuseTexture != nullptr)
        {
            _diffuseTexture->bind(1);
        }

        if (_specularTexture != nullptr)
        {
           _specularTexture->bind(2);
        }
    }

    void unbind()
    {
        if (_ambientTexture != nullptr)
        {
            _ambientTexture->unbind();
        }

        if (_diffuseTexture != nullptr)
        {
            _diffuseTexture->unbind();
        }

        if (_specularTexture != nullptr)
        {
           _specularTexture->unbind();
        }
    }

private:
    std::string _name;
    glm::vec3 _ambientColor;
    glm::vec3 _diffuseColor;
    glm::vec3 _specularColor;
    int _specularExponent;
    std::unique_ptr<Texture> _ambientTexture;
    std::unique_ptr<Texture> _diffuseTexture;
    std::unique_ptr<Texture> _specularTexture;
};
