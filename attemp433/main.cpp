#include "Game.h"

#include "ObjLoader.h"

int main()
{
    Game game("attempt443", 1920, 1080, 4, 5, false);

    // models

    std::shared_ptr<Model> floor = std::make_shared<Model>(glm::vec3(0.f));
    floor->load("images/plane.obj");

    // game

    game.addModel(floor);

    while (!game.getWindowShouldClose())
    {
        game.update();
        game.render();
    }

    return 0;
}
