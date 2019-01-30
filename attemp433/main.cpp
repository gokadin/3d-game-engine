#include "libs.h"

#include <memory>

#include "Scene.h"
#include "Game.h"
#include "enums.h"

int main()
{
    Game game("attempt443", 1920, 1080, 4, 5, false);
    game.loadScene("assets");
    game.getScene()->getWorld().getPhysics().enableGravity();

    // input

    game.getInputManager().onKeyDown(GLFW_KEY_B, [](std::unique_ptr<Scene>& scene)
    {
        scene->getModel("cube")->addVelocity(glm::vec3(0.f, 1.f, 0.f));
    });

    game.getInputManager().onKeyUp(GLFW_KEY_B, [](std::unique_ptr<Scene>& scene)
    {
        scene->getModel("cube")->addVelocity(glm::vec3(0.f, -1.f, 0.f));
    });

    game.getInputManager().onKeyDown(GLFW_KEY_N, [](std::unique_ptr<Scene>& scene)
    {
        scene->getModel("cube")->addVelocity(glm::vec3(0.f, -1.f, 0.f));
    });

    game.getInputManager().onKeyUp(GLFW_KEY_N, [](std::unique_ptr<Scene>& scene)
    {
        scene->getModel("cube")->addVelocity(glm::vec3(0.f, 1.f, 0.f));
    });

    game.getInputManager().onKeyPress(GLFW_KEY_ESCAPE, [](std::unique_ptr<Scene>& scene)
    {
        scene->closeWindow();
    });

    game.getInputManager().onKeyPress(GLFW_KEY_W, [](std::unique_ptr<Scene>& scene)
    {
        scene->getCamera().move(AT_CAMERA_DIRECTION_FORWARD);
    });

    game.getInputManager().onKeyPress(GLFW_KEY_S, [](std::unique_ptr<Scene>& scene)
    {
        scene->getCamera().move(AT_CAMERA_DIRECTION_BACKWARD);
    });

    game.getInputManager().onKeyPress(GLFW_KEY_A, [](std::unique_ptr<Scene>& scene)
    {
        scene->getCamera().move(AT_CAMERA_DIRECTION_LEFT);
    });

    game.getInputManager().onKeyPress(GLFW_KEY_D, [](std::unique_ptr<Scene>& scene)
    {
        scene->getCamera().move(AT_CAMERA_DIRECTION_RIGHT);
    });

    game.getInputManager().onMouseMove([](std::unique_ptr<Scene>& scene, const double& offsetX, const double& offsetY)
    {
        scene->getCamera().updateMouseInput(offsetX, offsetY);
    });

    while (!game.getWindowShouldClose())
    {
        game.update();
        game.render();
    }

    return 0;
}
