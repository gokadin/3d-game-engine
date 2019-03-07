#pragma once

#include <map>
#include <string>
#include <memory>

#include "Model.h"

class CollisionManager
{
public:
    CollisionManager();

    ~CollisionManager();

    void updateCollisions(const std::map<std::string, std::shared_ptr<Model>>& models);
};

