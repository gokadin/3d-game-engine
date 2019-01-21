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
            if (!otherModel->getPhysics().isCollisionEnabled() || otherModel->getId() == model->getId())
            {
                continue;
            }

            model->getPhysics().getCollision().isColliding(otherModel->getFuturePosition());
        }
    }
}
