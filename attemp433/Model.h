#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class Model
{
private:
    Material* _material;
    Texture* _overrideTextureDiffuse;
    Texture* _overrideTextureSpecular;
    std::vector<Mesh*> _meshes;
    glm::vec3 _position;

    void updateUniforms()
    {

    }

public:
    Model(
        glm::vec3 position,
        Material* material, 
        Texture* overrideTextureDiffuse,
        Texture* overrideTextureSpecular,
        std::vector<Mesh*> meshes
    )
        : _position(position)
        , _material(material)
        , _overrideTextureDiffuse(overrideTextureDiffuse)
        , _overrideTextureSpecular(overrideTextureSpecular)
    {
        for (auto* i : meshes)
        {
            _meshes.push_back(new Mesh(*i));
        }

        for (auto* i : _meshes)
        {
            i->move(_position);
        }
    }

    ~Model()
    {
        for (auto*& i : _meshes)
        {
            delete i;
        }
    }

    void rotate(glm::vec3 rotation)
    {
        for (auto& i : _meshes)
        {
            i->rotate(rotation);
        }
    }

    void update()
    {

    }

    void render(Shader* shader)
    {
        this->updateUniforms();

        _material->sendToShader(*shader);

        shader->use();

        _overrideTextureDiffuse->bind(0);
        _overrideTextureSpecular->bind(1);

        for (auto& i : _meshes)
        {
            i->render(shader);
        }
    }
};
