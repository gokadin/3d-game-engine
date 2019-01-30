#pragma once

#include "WorldPhysics.h"

class World
{
public:
    World();

    ~World();

    WorldPhysics& getPhysics() { return _physics; }
    
private:
    WorldPhysics _physics;
};

