#pragma once

#include <vector>
#include <memory>

#include "Shader.h"
#include "BoundingBox.h"

class Collision
{
public:
    Collision();

    ~Collision();

    void addBoundingBox(glm::vec3 position, glm::vec3 size);

    void renderDebug(Shader* shader);

    void move(glm::vec3 position);

    bool isColliding(Collision& other);

    inline void setCollided(bool value) { _hasCollided = value; }

    inline bool hasCollided() const { return _hasCollided; }

    inline const BoundingBox& getBoundingBox() { return _boundingBox; }

    void update();

private:
    BoundingBox _boundingBox;

    bool _hasCollided;
};

