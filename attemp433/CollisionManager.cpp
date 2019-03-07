#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::updateCollisions(const std::map<std::string, std::shared_ptr<Model>>& models)
{
    for (auto& [name, model] : models)
    {
        if (!model->getPhysics().isCollisionEnabled())
        {
            continue;
        }

        for (auto& [otherName, otherModel] : models)
        {
            if (!otherModel->getPhysics().isCollisionEnabled() || otherName == name)
            {
                continue;
            }

            if (model->getPhysics().getCollision().isColliding(otherModel->getPhysics().getCollision()))
            {
                std::cout << "HAS COLLIDED" << std::endl;

                model->setVelocity(glm::vec3(0.f));
                otherModel->setVelocity(glm::vec3(0.f));

                model->getPhysics().getCollision().setCollided(true);
            }
        }
    }
}
