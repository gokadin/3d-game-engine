#include "ModelRegistry.h"

ModelRegistry::ModelRegistry()
{
}

ModelRegistry::~ModelRegistry()
{
}

void ModelRegistry::registerModel(std::shared_ptr<Model> model)
{
    _models[model->getName()] = model;
}

std::shared_ptr<Model> ModelRegistry::findModel(const std::string& name)
{
    return _models.find(name) == _models.end() ? nullptr : _models[name];
}
