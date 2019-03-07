#include "ModelLoader.h"

ModelLoader::ModelLoader(Registry& registry)
    : _registry(registry), _objLoader(registry)
{
}

ModelLoader::~ModelLoader()
{
}

void ModelLoader::load(const std::string& rootDirectory)
{
    std::filesystem::path root(rootDirectory);
    if (!std::filesystem::exists(root))
    {
        std::cout << "error::ModelLoader::load::could_not_find_root_directory: " << rootDirectory << std::endl;
    }

    for (auto& modelDirectory : std::filesystem::directory_iterator(rootDirectory))
    {
        this->loadModel(std::filesystem::absolute(modelDirectory.path()).string());
    }
}

void ModelLoader::loadModel(const std::string& directory)
{
    std::string modelFile = this->findModelFile(directory);
    if (modelFile.empty())
    {
        std::cout << "error::ModelLoader::loadModel::could_not_find_model_file in: " << directory << std::endl;
        return;
    }

    std::shared_ptr<Model> model = this->parseModel(modelFile, directory);
    if (model == nullptr)
    {
        std::cout << "error::ModelLoader::loadModel::could_not_load_model from: " << modelFile << std::endl;
        return;
    }

    _registry.registerModel(model);
}

const std::string ModelLoader::findModelFile(const std::string& directory)
{
    for (auto& file : std::filesystem::directory_iterator(directory))
    {
        if (file.path().extension() == ".model")
        {
            return file.path().string();
        }
    }

    return "";
}

std::shared_ptr<Model> ModelLoader::parseModel(const std::string& filename, const std::string& directory)
{
    std::ifstream file;
    file.open(filename);

    if (file.is_open())
    {
        std::shared_ptr<Model> model = std::make_shared<Model>();

        std::string line;
        while (std::getline(file, line))
        {
            this->parseLine(line, model, directory);
        }

        return model;
    }
    else
    {
        std::cout << "ModelLoader::parseModel::could_not_open_file " << filename << std::endl;
        return nullptr;
    }

    file.close();
}

void ModelLoader::parseLine(const std::string& line, std::shared_ptr<Model>& model, const std::string& directory)
{
    if (line.substr(0, 1) != "$")
    {
        return;
    }

    std::string variable = line.substr(1, line.find(":") - 1);
    std::string value = line.substr(line.find(":") + 2);

    if (variable == "position")
    {
        this->setPosition(value, model);
    }
    else if (variable == "name")
    {
        this->setName(value, model);
    }
    else if (variable == "size")
    {
        this->setSize(value, model);
    }
    else if (variable == "mesh_file")
    {
        this->loadMesh(value, model, directory);
    }
    else if (variable == "enable_gravity")
    {
        this->enableGravity(value, model);
    }
    else if (variable == "enable_collision")
    {
        this->enableCollision(value, model);
    }
    else if (variable == "bounding_box")
    {
        this->setBoundingBox(value, model);
    }
}

void ModelLoader::loadMesh(const std::string& str, std::shared_ptr<Model>& model, const std::string& directory)
{
    for (auto&[name, mesh] : _objLoader.load(directory + "/" + str))
    {
        model->addMesh(mesh);
    }
}

void ModelLoader::setName(const std::string& str, std::shared_ptr<Model>& model)
{
    std::istringstream iss(str);
    std::string name;
    iss >> name;

    model->setName(name);
}

void ModelLoader::setSize(const std::string& str, std::shared_ptr<Model>& model)
{
    std::istringstream iss(str);
    glm::vec3 size;
    iss >> size.x;
    iss >> size.y;
    iss >> size.z;

    model->setSize(size);
}

void ModelLoader::setPosition(const std::string& str, std::shared_ptr<Model>& model)
{
    std::istringstream iss(str);
    glm::vec3 position;
    iss >> position.x;
    iss >> position.y;
    iss >> position.z;

    model->setPosition(position);
}

void ModelLoader::enableGravity(const std::string& str, std::shared_ptr<Model>& model)
{
    if (str == "true")
    {
        model->getPhysics().enableGravity();
    }
}

void ModelLoader::enableCollision(const std::string& str, std::shared_ptr<Model>& model)
{
    if (str == "true")
    {
        model->getPhysics().enableCollision();
    }
}

void ModelLoader::setBoundingBox(const std::string& str, std::shared_ptr<Model>& model)
{
    if (str == "cube")
    {
        model->getPhysics().getCollision().addBoundingBox(model->getPosition(), model->getSize());
    }
    else
    {
        std::cout << "error::ModelLoader::setBoundingBox::bounding_box_type_unknown: " << str << std::endl;
    }
}
