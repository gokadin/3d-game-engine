#include "Game.h"

#include "ObjLoader.h"

int main()
{
    Game game("attempt443", 1920, 1080, 4, 5, false);
    game.getPhysics().enableGravity();

    // models

    std::shared_ptr<Model> floor = std::make_shared<Model>(glm::vec3(0.f));
    floor->getPhysics().enableCollision();
    floor->load("images/plane.obj");

    std::shared_ptr<Model> cube = std::make_shared<Model>(glm::vec3(0.f, 3.f, 0.f));
    cube->getPhysics().enableCollision();
    cube->getPhysics().enableGravity();
    cube->load("images/cube.obj");

    // game

    game.addModel(floor);
    game.addModel(cube);

    while (!game.getWindowShouldClose())
    {
        game.update();
        game.render();
    }

    return 0;
}
