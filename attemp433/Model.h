#pragma once

#include <map>

#include "Mesh.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "ItemPhysics.h"

class Model
{
private:
    uint32_t _id;
    std::vector<std::shared_ptr<Mesh>> _meshes;
    glm::vec3 _position;
    glm::vec3 _displacement;
    ItemPhysics _physics;

    ObjLoader _objLoader;

public:
    Model(glm::vec3 position);

    ~Model();

    inline const uint32_t getId() { return _id; }

    inline ItemPhysics& getPhysics() { return _physics; }

    void load(std::string filename);

    inline const glm::vec3& getPosition() { return _position; }

    void setDisplacement(const glm::vec3 displacement);

    void move(const glm::vec3 displacement);

    const glm::vec3& getFuturePosition();

    void rotate(glm::vec3 rotation);

    void update();

    void render(Shader* shader);

    void commit();
};
