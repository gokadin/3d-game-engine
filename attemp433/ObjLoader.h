#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include <glm.hpp>

#include "Vertex.h"
#include "Mesh.h"
#include "MeshMaterial.h"
#include "MaterialParser.h"
#include "SubMesh.h"

class ObjLoader
{
private:
    std::string _objFilename;

    MaterialParser _materialParser;

    std::vector<glm::vec3> _positions;
    std::vector<glm::vec2> _texcoords;
    std::vector<glm::vec3> _normals;
    std::vector<Vertex> _vertices;

    std::map<std::string, std::shared_ptr<MeshMaterial>> _materials;
    std::map<std::string, std::shared_ptr<Mesh>> _meshes;

    bool wasLastLineVertex;
    std::string _currentMeshName;
    std::string _currentMaterialName;

    void parseLine(std::string& line)
    {
        if (line.substr(0, 2) == "f ")
        {
            wasLastLineVertex = true;
            this->parseVertexLine(line);
        }
        else
        {
            if (wasLastLineVertex)
            {
                // end of vertex group

                _meshes[_currentMeshName]->addSubMesh(std::make_shared<SubMesh>(
                    _materials[_currentMaterialName], 
                    _vertices
                    ));

                _vertices.clear();
            }

            wasLastLineVertex = false;
        }

        if (line.substr(0, 7) == "mtllib ")
        {
            this->parseMaterialLine(line);
        }

        if (line.substr(0, 7) == "usemtl ")
        {
            this->parseUseMaterialLine(line);
        }

        if (line.substr(0, 2) == "v ")
        {
            this->parsePositionLine(line);
        }

        if (line.substr(0, 3) == "vn ")
        {
            this->parseNormalLine(line);
        }

        if (line.substr(0, 3) == "vt ")
        {
            this->parseTexcoordsLine(line);
        }

        if (line.substr(0, 2) == "g ")
        {
            this->parseObjectNameLine(line);
        }
    }

    void parseMaterialLine(std::string& line)
    {
        std::string data = line.substr(7);
        std::string path = _objFilename.substr(0, _objFilename.rfind("/") + 1);
        std::string materialFilename = path + data;

        _materials = _materialParser.parse(materialFilename);
    }

    void parseUseMaterialLine(std::string& line)
    {
        _currentMaterialName = line.substr(7);
    }

    void parsePositionLine(std::string& line)
    {
        std::string data = line.substr(2);
        std::istringstream iss(data);

        glm::vec3 position;
        iss >> position.x;
        iss >> position.y;
        iss >> position.z;

        _positions.push_back(position);
    }

    void parseNormalLine(std::string& line)
    {
        std::string data = line.substr(3);
        std::istringstream iss(data);

        glm::vec3 normal;
        iss >> normal.x;
        iss >> normal.y;
        iss >> normal.z;

        _normals.push_back(normal);
    }

    void parseTexcoordsLine(std::string& line)
    {
        std::string data = line.substr(3);
        std::istringstream iss(data);

        glm::vec2 texcoord;
        iss >> texcoord.x;
        iss >> texcoord.y;

        _texcoords.push_back(texcoord);
    }

    void parseObjectNameLine(std::string& line)
    {
        std::string data = line.substr(2);
        std::istringstream iss(data);

        std::string name;
        iss >> name;

        _currentMeshName = name;
        _meshes[_currentMeshName] = std::make_shared<Mesh>();
    }

    void parseVertexLine(std::string& line)
    {
        std::string data = line.substr(2);
        std::istringstream iss(data);
        
        std::string indicesStr1, indicesStr2, indicesStr3;
        iss >> indicesStr1;
        iss >> indicesStr2;
        iss >> indicesStr3;

        this->addVertexFromIndicesString(indicesStr1);
        this->addVertexFromIndicesString(indicesStr2);
        this->addVertexFromIndicesString(indicesStr3);
    }

    void addVertexFromIndicesString(std::string& indicesStr)
    {
        std::string token;
        std::vector<std::string> split;
        std::istringstream iss(indicesStr);
        while (std::getline(iss, token, '/'))
        {
            split.push_back(token);
        }

        if (split.size() != 3)
        {
            std::cout << "error::ObjLoader::addVertexFromIndicesString::invalid_indices_string: " << indicesStr << std::endl;
            return;
        }

        _vertices.push_back(Vertex{_positions[stoi(split[0]) - 1], _texcoords[stoi(split[1]) - 1], _normals[stoi(split[2]) - 1]});
    }

public:
    ObjLoader()
        : wasLastLineVertex(false) { }

    std::map<std::string, std::shared_ptr<Mesh>>& load(std::string filename)
    {
        std::cout << "loading " << filename << std::endl;

        _objFilename = filename;

        std::ifstream file;
        file.open(filename);

        if (file.is_open())
        {
            std::string line;

            while (std::getline(file, line))
            {
                this->parseLine(line);
            }
        }
        else
        {
            std::cout << "ObjLoader::load::could_not_open_file " << filename << std::endl;
        }

        file.close();

        return _meshes;
    }

    inline Vertex* getVertices() { return _vertices.data(); }

    inline unsigned int getNumberOfVertices() { return _vertices.size(); }

    void print()
    {
        for (size_t i = 0; i < _vertices.size(); i++)
        {
            std::cout 
                << "pos: " << _vertices[i].position.x << " " << _vertices[i].position.y << " " << _vertices[i].position.z 
                << " tex: " << _vertices[i].texcoord.x << " " << _vertices[i].texcoord.y
                << " normal: " << _vertices[i].normal.x << " " << _vertices[i].normal.y << " " << _vertices[i].normal.z
                << std::endl;
        }
    }
};
