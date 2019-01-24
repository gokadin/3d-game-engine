#include "Model.h"

Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : _position(position), _rotation(rotation), _scale(scale)
    , _displacement(glm::vec3(0.f))
{
    this->updateModelMatrix();
}

Model::~Model()
{
}

void Model::setDisplacement(const glm::vec3 displacement)
{
    _displacement = displacement;
}

const glm::vec3 & Model::getFuturePosition()
{
    return _position + _displacement;
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
    this->updateModelMatrix();
    this->updateUniforms(shader);

    for (auto& mesh : _meshes)
    {
        mesh->render(shader);
    }

    //_physics.renderDebug(shader);
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
        //mesh->move(_displacement);
    }

    _displacement = glm::vec3(0.f);
}
