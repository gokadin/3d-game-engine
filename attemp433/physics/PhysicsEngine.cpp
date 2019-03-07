#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{

}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::update(WorldPhysics& worldPhysics, std::map<std::string, std::shared_ptr<Model>> models, const float& dt)
{
    if (!worldPhysics.isGravityEnabled())
    {
        return;
    }

    for (auto& [name, model] : models)
    {
        if (!model->getPhysics().isGravityEnabled())
        {
            continue;
        }

        model->addVelocity(glm::vec3(0.f, -9.8f / 60.f, 0.f));
    }
}
