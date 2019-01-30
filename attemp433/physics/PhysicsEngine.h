#pragma once

#include <map>
#include <memory>
#include <string>

#include "../WorldPhysics.h"
#include "../Model.h"

class PhysicsEngine
{
public:
    PhysicsEngine();

    ~PhysicsEngine();

    void update(WorldPhysics& worldPhysics, std::map<std::string, std::shared_ptr<Model>> models, const float& dt);

private:
};