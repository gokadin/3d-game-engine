#pragma once

#include <map>
#include <string>
#include <memory>
#include <iostream>

#include "../Model.h"

class ModelRegistry
{
public:
    ModelRegistry();

    ~ModelRegistry();

    void registerModel(std::shared_ptr<Model> model);

    std::shared_ptr<Model> findModel(const std::string& name);

    std::map<std::string, std::shared_ptr<Model>> getModels() { return _models; }

private:
    std::map<std::string, std::shared_ptr<Model>> _models;
};

