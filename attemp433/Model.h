#pragma once

#include <map>

#include "Mesh.h"
#include "Shader.h"
#include "ObjLoader.h"

class Model
{
private:
    std::vector<Mesh*> _meshes;
    glm::vec3 _position;

    ObjLoader _objLoader;

public:
    Model(glm::vec3 position)
        : _position(position) { }

    ~Model()
    {
        for (auto*& i : _meshes)
        {
            delete i;
        }
        _meshes.clear();
    }

    void load(std::string filename)
    {
        for (auto const&[key, value] : _objLoader.load(filename))
        {
            _meshes.push_back(value);
        }

        for (auto* i : _meshes)
        {
            i->move(_position);
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
