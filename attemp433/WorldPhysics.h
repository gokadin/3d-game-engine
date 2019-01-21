#pragma once

#include <vector>
#include <memory>

#include "Model.h"

class WorldPhysics
{
public:
    WorldPhysics();

    ~WorldPhysics();

    inline void enableGravity() { _gravityEnabled = true; }

    void updateModels(const std::vector<std::shared_ptr<Model>>& models);

private:
    bool _gravityEnabled;

    void updateModelGravity(const std::shared_ptr<Model>& model);
};

