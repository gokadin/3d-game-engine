#include "Registry.h"

Registry::Registry()
{
}

Registry::~Registry()
{
}

void Registry::registerModel(std::shared_ptr<Model> model)
{
    _modelRegistry.registerModel(model);
}

void Registry::registerMaterial(std::shared_ptr<MeshMaterial> material)
{
    _materialRegistry.registerMaterial(material);
}

std::shared_ptr<Model> Registry::findModel(const std::string& name)
{
    return _modelRegistry.findModel(name);
}

std::shared_ptr<MeshMaterial> Registry::findMaterial(const std::string& name)
{
    return _materialRegistry.findMaterial(name);
}
