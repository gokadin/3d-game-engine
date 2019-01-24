#pragma once

#include <map>
#include <string>
#include <memory>

#include "Model.h"

class ModelRegistry
{
public:
    ModelRegistry();

    ~ModelRegistry();

private:
    std::map<std::string, std::shared_ptr<Model>> _models;
};

