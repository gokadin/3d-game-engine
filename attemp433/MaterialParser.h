#pragma once

#include <map>
#include <string>

#include "MeshMaterial.h"

class MaterialParser
{
public:
    std::map<std::string, std::shared_ptr<MeshMaterial>>& parse(std::string filename)
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
            std::cout << "MaterialParser::parse::could_not_open_file " << filename << std::endl;
        }

        file.close();

        return _materials;
    }

    ~MaterialParser()
    {
        _materials.clear();
    }

private:
    std::map<std::string, std::shared_ptr<MeshMaterial>> _materials;
    std::string _currentMaterialName;

    void parseLine(std::string& line)
    {
        if (line.substr(0, 7) == "newmtl ")
        {
            this->parseNameLine(line);
        }

        if (line.substr(0, 4) == "\tKa ")
        {
            this->parseAmbientLine(line);
        }

        if (line.substr(0, 4) == "\tKd ")
        {
            this->parseDiffuseLine(line);
        }

        if (line.substr(0, 4) == "\tKs ")
        {
            this->parseSpecularLine(line);
        }

        if (line.substr(0, 4) == "\tNs ")
        {
            this->parseSpecularExponentLine(line);
        }

        if (line.substr(0, 8) == "\tmap_Ka ")
        {
            this->parseAmbientTextureLine(line);
        }

        if (line.substr(0, 8) == "\tmap_Kd ")
        {
            this->parseDiffuseTextureLine(line);
        }

        if (line.substr(0, 8) == "\tmap_Ks ")
        {
            this->parseSpecularTextureLine(line);
        }
    }

    void parseNameLine(std::string& line)
    {
        _currentMaterialName = line.substr(7);

        _materials[_currentMaterialName] = std::make_shared<MeshMaterial>(_currentMaterialName);
    }

    void parseAmbientLine(std::string& line)
    {
        std::string data = line.substr(4);
        std::istringstream iss(data);

        glm::vec3 color;
        iss >> color.x;
        iss >> color.y;
        iss >> color.z;

        _materials[_currentMaterialName]->setAmbientColor(color);
    }

    void parseDiffuseLine(std::string& line)
    {
        std::string data = line.substr(4);
        std::istringstream iss(data);

        glm::vec3 color;
        iss >> color.x;
        iss >> color.y;
        iss >> color.z;

        _materials[_currentMaterialName]->setDiffuseColor(color);
    }

    void parseSpecularLine(std::string& line)
    {
        std::string data = line.substr(4);
        std::istringstream iss(data);

        glm::vec3 color;
        iss >> color.x;
        iss >> color.y;
        iss >> color.z;

        _materials[_currentMaterialName]->setSpecularColor(color);
    }

    void parseSpecularExponentLine(std::string& line)
    {
        std::string data = line.substr(4);
        std::istringstream iss(data);

        int exponent;
        iss >> exponent;

        _materials[_currentMaterialName]->setSpecularExponent(exponent);
    }

    void parseAmbientTextureLine(std::string& line)
    {
        std::string filename = line.substr(8);

        _materials[_currentMaterialName]->addAmbientTexture(filename);
    }

    void parseDiffuseTextureLine(std::string& line)
    {
        std::string filename = line.substr(8);

        _materials[_currentMaterialName]->addDiffuseTexture(filename);
    }

    void parseSpecularTextureLine(std::string& line)
    {
        std::string filename = line.substr(8);

        _materials[_currentMaterialName]->addSpecularTexture(filename);
    }
};
