#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>

class Shader
{
private:
    GLuint _id;
    const int _versionMajor;
    const int _versionMinor;

    std::string loadShaderSource(std::string filename)
    {
        std::string temp = "";
        std::string src = "";

        std::ifstream in_file;
        in_file.open(filename);

        if (in_file.is_open())
        {
            while (std::getline(in_file, temp))
            {
                src += temp + "\n";
            }
        }
        else
        {
            std::cout << "error::Shader::loadShaderSource::could_no_open_file " << filename << std::endl;
        }

        in_file.close();

        std::string version = std::to_string(_versionMajor) + std::to_string(_versionMinor) + "0";
        src.replace(src.find("#version"), 12, "#version " + version);

        return src;
    }

    GLuint loadShader(GLenum type, std::string filename)
    {
        char infoLog[512];
        GLint success;

        GLuint shader = glCreateShader(type);
        std::string str_src = this->loadShaderSource(filename);
        const GLchar* src = str_src.c_str();
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "error::Shader::loadShader::could_no_compile_shader" << filename << std::endl;
            std::cout << infoLog << std::endl;
        }

        return shader;
    }

    void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
    {
        char infoLog[512];
        GLint success;

        _id = glCreateProgram();

        glAttachShader(_id, vertexShader);

        if (geometryShader) {
            glAttachShader(_id, geometryShader);
        }

        glAttachShader(_id, fragmentShader);

        glLinkProgram(_id);

        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(_id, 512, NULL, infoLog);
            std::cout << "error::Shader::linkProgram::could_no_link_program" << std::endl;
            std::cout << infoLog << std::endl;
        }

        glUseProgram(0);
    }

public:
    Shader(
        const int versionMajor, const int versionMinor,
        std::string vertexFile, std::string fragmentFile, std::string geometryFile = ""
    )
        : _versionMajor(versionMajor), _versionMinor(versionMinor)
    {
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
        if (geometryFile != "")
        {
           geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
        }
        fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

        this->linkProgram(vertexShader, geometryShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);
    }

    ~Shader()
    {
        glDeleteProgram(_id);
    }

    void use()
    {
        glUseProgram(_id);
    }

    void unuse()
    {
        glUseProgram(0);
    }

    void set1f(GLfloat value, const GLchar* name)
    {
        this->use();

        glUniform1f(glGetUniformLocation(_id, name), value);

        this->unuse();
    }

    void set1i(GLint value, const GLchar* name)
    {
        this->use();

        glUniform1i(glGetUniformLocation(_id, name), value);

        this->unuse();
    }

    void setVec2f(glm::fvec2 value, const GLchar* name)
    {
        this->use();

        glUniform2fv(glGetUniformLocation(_id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void setVec3f(glm::fvec3 value, const GLchar* name)
    {
        this->use();

        glUniform3fv(glGetUniformLocation(_id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void setVec4f(glm::fvec4 value, const GLchar* name)
    {
        this->use();

        glUniform4fv(glGetUniformLocation(_id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
    {
        this->use();

        glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, transpose, glm::value_ptr(value));

        this->unuse();
    }

    void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
    {
        this->use();

        glUniformMatrix3fv(glGetUniformLocation(_id, name), 1, transpose, glm::value_ptr(value));

        this->unuse();
    }
};
