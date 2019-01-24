#include "Game.h"

int main()
{
    Game game("attempt443", 1920, 1080, 4, 5, false);
    game.load("assets");
    game.getPhysics().enableGravity();

    // models

    //std::shared_ptr<Model> floor = std::make_shared<Model>(glm::vec3(0.f));
    //floor->getPhysics().enableCollision();
    //floor->getPhysics().getCollision().addBoundingBox(glm::vec3(0.f), glm::vec3(100.f, 1.f, 100.f));
    //floor->load("images/plane.obj");

    //std::shared_ptr<Model> cube = std::make_shared<Model>(glm::vec3(0.f, 5.f, 0.f));
    //cube->getPhysics().enableCollision();
    //cube->getPhysics().getCollision().addBoundingBox(glm::vec3(0.f, 5.f, 0.f), glm::vec3(5.f, 5.f, 5.f));
    //cube->getPhysics().enableGravity();
    //cube->load("assets/models/cube/cube.obj");

    // game

    //game.addModel(floor);
    //game.addModel(cube);

    while (!game.getWindowShouldClose())
    {
        game.update();
        game.render();
    }

    return 0;
}
