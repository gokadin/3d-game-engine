#pragma once

#include <string>
#include <filesystem>
#include <iostream>

class GameLoader
{
public:
    GameLoader();

    ~GameLoader();

    void load(const std::string& rootDirectory);
};

