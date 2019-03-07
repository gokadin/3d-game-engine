#pragma once

#include <memory>

#include "ModelRegistry.h"
#include "MaterialRegistry.h"
#include "../Model.h"
#include "../MeshMaterial.h"

class Registry
{
public:
    Registry();

    ~Registry();

    void registerModel(std::shared_ptr<Model> model);
    void registerMaterial(std::shared_ptr<MeshMaterial> material);

    std::shared_ptr<Model> findModel(const std::string& name);
    std::shared_ptr<MeshMaterial> findMaterial(const std::string& name);

    std::map<std::string, std::shared_ptr<Model>> getModels() { return _modelRegistry.getModels(); }

private:
    ModelRegistry _modelRegistry;
    MaterialRegistry _materialRegistry;
};

