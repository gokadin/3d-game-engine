#pragma once

#include "WorldPhysics.h"

class World
{
public:
    World();

    ~World();

    inline WorldPhysics& getPhysics() { return _physics; }
    
private:
    WorldPhysics _physics;
};

