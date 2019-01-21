#pragma once

#include <glm.hpp>
#include <vec3.hpp>

#include "Collision.h"
#include "Shader.h"

class ItemPhysics
{
public:
    ItemPhysics()
        : _gravityEnabled(false), _collisionEnabled(false)
        , _acceleration(glm::vec3(0.f)) { }

    inline Collision& getCollision() { return _collision; }

    void renderDebug(Shader* shader)
    {
        _collision.renderDebug(shader);
    }

    inline void enableGravity() { _gravityEnabled = true; }
    inline void enableCollision() { _collisionEnabled = true; }

    inline bool isGravityEnabled() { return _gravityEnabled; }
    inline bool isCollisionEnabled() { return _collisionEnabled; }

    glm::vec3 calculateFallAcceleration()
    {

    }

private:
    Collision _collision;

    bool _gravityEnabled;
    bool _collisionEnabled;

    glm::vec3 _acceleration;
};
