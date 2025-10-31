#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaders.h"

class Texture
{
    public:
        GLuint ID;
        GLenum type;
        Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

        void texUnit(Shaders& shader, const char* uniform, GLuint unit);
        void bind();
        void unbind();
        void remove();
};

#endif