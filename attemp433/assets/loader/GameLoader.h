#pragma once

#include <string>
#include <filesystem>
#include <iostream>

#include "Registry.h"
#include "ModelLoader.h"

class GameLoader
{
public:
    GameLoader();

    ~GameLoader();

    void load(const std::string& rootDirectory);

    inline Registry& getRegistry() { return _registry; }

private:
    const std::string MODEL_DIRECTORY = "models";

    Registry _registry;

    ModelLoader _modelLoader;
};

