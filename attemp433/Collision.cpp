#include "Collision.h"


Collision::Collision()
    : _minX(999.f), _maxX(-999.f), _minY(999.f), _maxY(-999.f), _minZ(999.f), _maxZ(-999.f)
{
    std::vector<Vertex> vertices;
    Vertex v1, v2, v3;
    v1.position = glm::vec3(1.f, 1.f, 0.f);
    v2.position = glm::vec3(1.f, 0.f, 0.f);
    v3.position = glm::vec3(0.f, 0.f, 0.f);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    std::shared_ptr<MeshMaterial> debugMaterial = std::make_shared<MeshMaterial>("debug");
    debugMaterial->setAmbientColor(glm::vec3(1.f, 0.f, 1.f));
    debugMaterial->setDiffuseColor(glm::vec3(0.7f, 0.f, 1.f));

    _debugSubMesh = std::make_unique<SubMesh>(debugMaterial, vertices);
}

Collision::~Collision()
{

}

void Collision::addBoundingBox(const std::vector<std::shared_ptr<Mesh>>& meshes, const glm::vec3 & position)
{
    this->setEdgeCoordinates(meshes, position);

    std::vector<Vertex> vertices;
    Vertex v1, v2, v3, v4, v5, v6;
    v1.position = glm::vec3(_minX, _maxY, _maxZ); // left far
    v2.position = glm::vec3(_maxX, _maxY, _minZ); // right close
    v3.position = glm::vec3(_minX, _maxY, _minZ); // left close
    v4.position = glm::vec3(_minX, _maxY, _maxZ); // left far
    v5.position = glm::vec3(_maxX, _maxY, _maxZ); // right far
    v6.position = glm::vec3(_maxX, _maxY, _minZ); // right close
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);
    vertices.push_back(v6);

    std::shared_ptr<MeshMaterial> debugMaterial = std::make_shared<MeshMaterial>("debug");
    debugMaterial->setAmbientColor(glm::vec3(1.f, 0.5f, 0.5f));
    debugMaterial->setDiffuseColor(glm::vec3(0.7f, 0.5f, 1.f));

    _debugSubMesh = std::make_unique<SubMesh>(debugMaterial, vertices);
    _debugSubMesh->setPolygonMode(GL_LINE);
}

void Collision::renderDebug(Shader * shader)
{
    _debugSubMesh->render(shader);
}

void Collision::move(glm::vec3 position)
{
    _minX += position.x;
    _maxX += position.x;
    _minY += position.y;
    _maxY += position.y;
    _minZ += position.z;
    _maxZ += position.z;
}

bool Collision::isColliding(glm::vec3 position)
{
    std::cout << "Y: " << position.y << " maxY: " << _maxY << std::endl;

    bool a = (position.x >= _minX && position.x <= _maxX)
        && (position.y >= _minY && position.y <= _maxY)
        && (position.z >= _minZ && position.z <= _maxZ);

    std::cout << a << std::endl;

    return a;
}

void Collision::setEdgeCoordinates(const std::vector<std::shared_ptr<Mesh>>& meshes, const glm::vec3 & position)
{
    for (auto& mesh : meshes)
    {
        for (auto& subMesh : mesh->getSubMeshes())
        {
            Vertex* vertices = subMesh->getVertices();
            for (size_t i = 0; i < subMesh->getNumberOfVertices(); i++)
            {
                if (vertices[i].position.x < _minX)
                {
                    _minX = vertices[i].position.x;
                }

                if (vertices[i].position.x > _maxX)
                {
                    _maxX = vertices[i].position.x;
                }

                if (vertices[i].position.y < _minY)
                {
                    _minY = vertices[i].position.y;
                }

                if (vertices[i].position.y > _maxY)
                {
                    _maxY = vertices[i].position.y;
                }

                if (vertices[i].position.z < _minZ)
                {
                    _minZ = vertices[i].position.z;
                }

                if (vertices[i].position.z > _maxZ)
                {
                    _maxZ = vertices[i].position.z;
                }
            }
        }
    }

    _minX -= 0.1f;
    _maxX += 0.1f;
    _minY -= 0.1f;
    _maxY += 0.1f;
    _minZ -= 0.1f;
    _maxZ += 0.1f;
}
