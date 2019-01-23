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
        value->move(_position);
        _meshes.push_back(value);
    }
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
    if (!_physics.getCollision().hasCollided())
    {
        this->commit();
        _physics.getCollision().update();
    }
    else
    {
        _physics.getCollision().setCollided(false);
        _displacement = glm::vec3(0.f);
    }
}

void Model::render(Shader* shader)
{
    for (auto& mesh : _meshes)
    {
        mesh->render(shader);
    }

    _physics.renderDebug(shader);
}

void Model::move(const glm::vec3 displacement)
{
    _displacement = displacement;

    _physics.getCollision().move(displacement);
}

void Model::commit()
{
    _position += _displacement;

    for (auto& mesh : _meshes)
    {
        mesh->move(_displacement);
    }

    _displacement = glm::vec3(0.f);
}
