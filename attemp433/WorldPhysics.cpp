#include "WorldPhysics.h"

WorldPhysics::WorldPhysics()
    : _gravityEnabled(false)
{

}

WorldPhysics::~WorldPhysics()
{

}

void WorldPhysics::updateModels(const std::vector<std::shared_ptr<Model>>& models)
{
    for (auto& model : models)
    {
        if (_gravityEnabled)
        {
            this->updateModelGravity(model);
        }
    }
}

void WorldPhysics::updateModelGravity(const std::shared_ptr<Model>& model)
{
    if (model->getPhysics().isGravityEnabled())
    {
        glm::vec3 displacement = glm::vec3(0.f, -0.01f, 0.f);

        model->setDisplacement(displacement);
    }
}
