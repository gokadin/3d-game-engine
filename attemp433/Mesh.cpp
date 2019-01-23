#include "Mesh.h"

Mesh::Mesh(
    glm::vec3 position = glm::vec3(0.f),
    glm::vec3 rotation = glm::vec3(0.f),
    glm::vec3 scale = glm::vec3(1.f)
)
    : _position(position), _rotation(rotation), _scale(scale), _displacement(glm::vec3(0.f))
{
    _id = reinterpret_cast<uint32_t>(this);
    this->updateModelMatrix();
}

Mesh::~Mesh()
{
}

void Mesh::load(std::string filename)
{
    for (auto const&[key, value] : _objLoader.load(filename))
    {
        value->move(_position);
        _subMeshes.push_back(value);
    }
}

void Mesh::setDisplacement(const glm::vec3 displacement)
{
    _displacement = displacement;
}

const glm::vec3 & Mesh::getFuturePosition()
{
    return _position + _displacement;
}

void Mesh::update()
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

void Mesh::render(Shader* shader)
{
    for (auto& mesh : _meshes)
    {
        mesh->render(shader);
    }

    _physics.renderDebug(shader);
}

void Mesh::move(const glm::vec3 displacement)
{
    _displacement = displacement;

    _physics.getCollision().move(displacement);
}

void Mesh::commit()
{
    _position += _displacement;

    for (auto& mesh : _meshes)
    {
        mesh->move(_displacement);
    }

    _displacement = glm::vec3(0.f);
}
