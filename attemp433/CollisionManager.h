#pragma once

#include <vector>
#include <memory>

#include "Model.h"

class CollisionManager
{
public:
    CollisionManager();

    ~CollisionManager();

    void updateCollisions(const std::vector<std::shared_ptr<Model>>& models);
};

