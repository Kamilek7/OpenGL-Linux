#ifndef VAO_H
#define VAO_H

#include <VBO.h>
class VAO
{

    public:
        GLuint ID;
        VAO();

        void linkAttributes(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
        void bind();
        void unbind();
        void remove();
};

#endif