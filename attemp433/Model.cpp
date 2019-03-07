#include "Model.h"

Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : _position(position), _rotation(rotation), _scale(scale)
    , _velocity(glm::vec3(0.f))
{
    this->updateModelMatrix();
}

Model::~Model()
{
}

void Model::update()
{
    _position += _velocity * (1.f / 60.f);

    _physics.getCollision().move(_velocity * (1.f / 60.f));

    _physics.getCollision().update();
}

void Model::render(Shader* shader)
{
    this->updateModelMatrix();
    this->updateUniforms(shader);

    for (auto& mesh : _meshes)
    {
        mesh->render(shader);
    }
}
