#pragma once

#include "Mesh.h"
#include "Shader.h"

class Model2
{
private:
    std::vector<Mesh*> _meshes;
    glm::vec3 _position;

public:
    Model2(
        glm::vec3 position,
        std::vector<Mesh*> meshes
    )
        : _position(position)
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

    ~Model2()
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
        for (auto& i : _meshes)
        {
            i->render(shader);
        }
    }
};
