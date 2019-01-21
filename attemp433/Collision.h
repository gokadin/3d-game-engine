#pragma once

#include <vector>
#include <memory>

#include "Shader.h"
#include "SubMesh.h"
#include "Mesh.h"
#include "Vertex.h"

class Collision
{
public:
    Collision();

    ~Collision();

    void addBoundingBox(const std::vector<std::shared_ptr<Mesh>>& meshes, const glm::vec3& position);

    void renderDebug(Shader* shader);

    void move(glm::vec3 position);

    bool isColliding(glm::vec3 position);

private:
    std::unique_ptr<SubMesh> _debugSubMesh;

    float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;

    void setEdgeCoordinates(const std::vector<std::shared_ptr<Mesh>>& meshes, const glm::vec3 & position);
};

