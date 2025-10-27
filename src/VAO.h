#ifndef VAO_H
#define VAO_H

#include <VBO.h>
class VAO
{

    public:
        GLuint ID;
        VAO();

        void linkVBO(VBO VBO, GLuint layout);
        void bind();
        void unbind();
        void remove();
};

#endif