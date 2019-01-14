#include "Game.h"

#include "ObjLoader.h"

int main()
{
    Game game("attempt443", 1920, 1080, 4, 5, false);

    while (!game.getWindowShouldClose())
    {
        game.update();
        game.render();
    }

    return 0;
}
