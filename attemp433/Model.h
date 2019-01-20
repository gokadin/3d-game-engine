#pragma once

#include <map>

#include "Mesh.h"
#include "Shader.h"
#include "ObjLoader.h"

class Model
{
private:
    std::vector<std::shared_ptr<Mesh>> _meshes;
    glm::vec3 _position;

    ObjLoader _objLoader;

public:
    Model(glm::vec3 position)
        : _position(position) { }

    ~Model()
    {
       _meshes.clear();
    }

    void load(std::string filename)
    {
        for (auto const&[key, value] : _objLoader.load(filename))
        {
            _meshes.push_back(value);
        }

        for (auto& mesh : _meshes)
        {
            mesh->move(_position);
        }
    }

    void rotate(glm::vec3 rotation)
    {
        for (auto& mesh : _meshes)
        {
            mesh->rotate(rotation);
        }
    }

    void update()
    {

    }

    void render(Shader* shader)
    {
        for (auto& mesh : _meshes)
        {
            mesh->render(shader);
        }
    }
};
