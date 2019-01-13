#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glm.hpp>

#include "Vertex.h"

class ObjLoader
{
private:
    std::vector<glm::vec3> _positions;
    std::vector<glm::vec2> _texcoords;
    std::vector<glm::vec3> _normals;
    std::vector<unsigned int> _indices;
    std::vector<Vertex> _vertices;

    void parseLine(std::string& line)
    {
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

        if (line.substr(0, 2) == "f")
        {
            this->parseVertexLine(line);
        }
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

    void parseVertexLine(std::string& line)
    {
        std::string data = line.substr(2);
        std::istringstream iss(data);

        unsigned int positionIndex;
        unsigned int texcoordIndex;
        unsigned int normalIndex;
        iss >> positionIndex;
        iss >> texcoordIndex;
        iss >> normalIndex;

        _vertices.push_back(Vertex(
            _positions.at(positionIndex),
            _texcoords.at(texcoordIndex),
            _normals.at(normalIndex)
        ));
    }

public:
    void load(std::string filename)
    {
        std::cout << "loading " << filename << std::endl;

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
    }

    void print()
    {
        for (size_t i = 0; i < _vertices.size(); i++)
        {
            std::cout 
                << "pos: " << _vertices[i].getPosition().x << " " << _vertices[i].getPosition().y << " " << _vertices[i].getPosition().z 
                << " tex: " << _vertices[i].getTexcoord().x << " " << _vertices[i].getTexcoord().y
                << " normal: " << _vertices[i].getNormal().x << " " << _vertices[i].getNormal().y << " " << _vertices[i].getNormal().z
                << std::endl;
        }
        for (auto& i : _vertices)
        {
            std::cout 
                << "pos: " << i.getPosition().x << " " << i.getPosition().y << " " << i.getPosition().z 
                << " tex: " << i.getTexcoord().x << " " << i.getTexcoord().y
                << " normal: " << i.getNormal().x << " " << i.getNormal().y << " " << i.getNormal().z
                << std::endl;
        }
    }
};
