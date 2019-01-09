#pragma once

#include <iostream>
#include <string>

#include <glew.h>
#include <glfw3.h>

#include <SOIL2.h>

class Texture
{
private:
    GLuint id;
    int width;
    int height;
    unsigned int type;

public:
    Texture(const char* filename, GLenum type)
        : type(type)
    {
        unsigned char* image = SOIL_load_image(filename, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

        glGenTextures(1, &this->id);
        glBindTexture(this->type, this->id);
     
        glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (image)
        {
            glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(this->type);
        }
        else
        {
            std::cout << "error::Texture::texture_loading_failed " << filename << std::endl;
        }

        glActiveTexture(0);
        glBindTexture(this->type, 0);
        SOIL_free_image_data(image);
    }

    ~Texture()
    {
        glDeleteTextures(1, &this->id);
    }

    inline GLuint getId() const { return this->id; }

    void bind(const GLint textureUnit)
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(this->type, this->id);;
    }

    void unbind()
    {
        glActiveTexture(0);
        glBindTexture(this->type, 0);
    }
};
