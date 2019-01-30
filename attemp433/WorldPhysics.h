#pragma once

#include <vector>
#include <memory>

class WorldPhysics
{
public:
    WorldPhysics();

    ~WorldPhysics();

    inline void enableGravity() { _gravityEnabled = true; }

    inline bool isGravityEnabled() { return _gravityEnabled; }

private:
    bool _gravityEnabled;
};

