#include "Game.h"

#include "ObjLoader.h"

int main()
{
    Game game("attempt443", 1920, 1080, 4, 5, false);

    // models

    Model* floor = new Model(glm::vec3(0.f));
    floor->load("images/floor.obj");

    // game

    game.addModel(floor);

    while (!game.getWindowShouldClose())
    {
        game.update();
        game.render();
    }

    // clean up

    delete floor;

    return 0;
}
