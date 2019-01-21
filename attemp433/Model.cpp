#include "Model.h"

Model::Model(glm::vec3 position)
    : _position(position), _displacement(glm::vec3(0.f))
{
    _id = reinterpret_cast<uint32_t>(this);
}

Model::~Model()
{
}

void Model::load(std::string filename)
{
    for (auto const&[key, value] : _objLoader.load(filename))
    {
        _meshes.push_back(value);
    }

    for (auto& mesh : _meshes)
    {
        mesh->move(_position);
    }

    _physics.getCollision().addBoundingBox(_meshes, _position);
}

void Model::setDisplacement(const glm::vec3 displacement)
{
    _displacement = displacement;
}

const glm::vec3 & Model::getFuturePosition()
{
    return _position + _displacement;
}

void Model::rotate(glm::vec3 rotation)
{
    for (auto& mesh : _meshes)
    {
        mesh->rotate(rotation);
    }
}

void Model::update()
{
    this->move();
}

void Model::render(Shader * shader)
{
    for (auto& mesh : _meshes)
    {
        mesh->render(shader);
    }

    _physics.renderDebug(shader);
}

void Model::move()
{
    _position += _displacement;

    for (auto& mesh : _meshes)
    {
        mesh->move(_displacement);
    }

    _physics.getCollision().move(_displacement);

    _displacement = glm::vec3(0.f);
}
