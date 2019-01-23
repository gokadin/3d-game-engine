#include "GameLoader.h"

GameLoader::GameLoader()
{
}

GameLoader::~GameLoader()
{
}

void GameLoader::load(const std::string& rootDirectory)
{
    std::filesystem::path root(rootDirectory);

    if (!std::filesystem::exists(root))
    {
        std::cout << "error::GameLoader::load::could_not_find_root_directory: " << rootDirectory << std::endl;
        return;
    }
}
