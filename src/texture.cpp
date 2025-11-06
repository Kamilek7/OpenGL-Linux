#include "texture.h"

Texture::Texture(const char* image, const char* texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;
    int width, height, numCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &width, &height, &numCh,0);

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shaders& shader, const char* uniform, GLuint unit)
{
    GLuint tex0 = glGetUniformLocation(shader.getID(), uniform);
    shader.useShader();
    glUniform1i(tex0,unit);
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0+unit);
    glBindTexture(GL_TEXTURE_2D,ID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::remove()
{
    glDeleteTextures(1,&ID);
}