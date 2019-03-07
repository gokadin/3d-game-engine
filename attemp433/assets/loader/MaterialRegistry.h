#pragma once

#include <map>
#include <memory>
#include <string>

#include "../MeshMaterial.h"

class MaterialRegistry
{
public:
    MaterialRegistry();

    ~MaterialRegistry();

    void registerMaterial(std::shared_ptr<MeshMaterial> material);

    std::shared_ptr<MeshMaterial> findMaterial(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<MeshMaterial>> _materials;
};

