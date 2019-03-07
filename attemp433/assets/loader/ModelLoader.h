#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "Registry.h"
#include "ObjLoader.h"

class ModelLoader
{
public:
    ModelLoader(Registry& registry);

    ~ModelLoader();

    void load(const std::string& rootDirectory);

private:
    Registry& _registry;
    ObjLoader _objLoader;

    void loadModel(const std::string& directory);

    const std::string findModelFile(const std::string& directory);

    std::shared_ptr<Model> parseModel(const std::string& filename, const std::string& directory);
    
    void parseLine(const std::string& line, std::shared_ptr<Model>& model, const std::string& directory);

    void loadMesh(const std::string& str, std::shared_ptr<Model>& model, const std::string& directory);
    void setName(const std::string& str, std::shared_ptr<Model>& model);
    void setSize(const std::string& str, std::shared_ptr<Model>& model);
    void setPosition(const std::string& str, std::shared_ptr<Model>& model);
    void enableGravity(const std::string& str, std::shared_ptr<Model>& model);
    void enableCollision(const std::string& str, std::shared_ptr<Model>& model);
    void setBoundingBox(const std::string& str, std::shared_ptr<Model>& model);
};

