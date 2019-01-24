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

    void printModelNames()
    {
        for (auto&[name, model] : _models)
        {
            std::cout << model->getSize().x << std::endl;
        }
    }

private:
    std::map<std::string, std::shared_ptr<Model>> _models;
};

