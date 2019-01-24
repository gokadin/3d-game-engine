#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::updateCollisions(const std::vector<std::shared_ptr<Model>>& models)
{
    for (auto& model : models)
    {
        if (!model->getPhysics().isCollisionEnabled())
        {
            continue;
        }

        for (auto& otherModel : models)
        {
            if (!otherModel->getPhysics().isCollisionEnabled() || otherModel->getName() == model->getName())
            {
                continue;
            }

            if (model->getPhysics().getCollision().isColliding(otherModel->getPhysics().getCollision()))
            {
                std::cout << "HAS COLLIDED" << std::endl;

                model->getPhysics().getCollision().setCollided(true);
            }
        }
    }
}
