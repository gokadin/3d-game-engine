#include "MaterialRegistry.h"

MaterialRegistry::MaterialRegistry()
{
}

MaterialRegistry::~MaterialRegistry()
{
}

void MaterialRegistry::registerMaterial(std::shared_ptr<MeshMaterial> material)
{
    _materials[material->getName()] = material;
}

std::shared_ptr<MeshMaterial> MaterialRegistry::findMaterial(const std::string& name)
{
    return _materials.find(name) == _materials.end() ? nullptr : _materials[name];
}
