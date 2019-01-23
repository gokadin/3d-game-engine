#include "Collision.h"


Collision::Collision()
{

}

Collision::~Collision()
{

}

void Collision::addBoundingBox(glm::vec3 position, glm::vec3 size)
{
    _boundingBox.initialize(position, size);
}

void Collision::renderDebug(Shader * shader)
{
    //_debugSubMesh->render(shader);
}

void Collision::move(glm::vec3 position)
{
    _boundingBox.move(position);
}

bool Collision::isColliding(Collision& other)
{
    _hasCollided = _boundingBox.isColliding(other.getBoundingBox());

    return _hasCollided;
}

void Collision::update()
{
    _boundingBox.update();
}
