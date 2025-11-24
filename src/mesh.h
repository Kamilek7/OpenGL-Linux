#ifndef MESH_H
#define MESH_H
#include <string>
#include "VAO.h"
#include "EBO.h"
#include "camera.h"
#include "texture.h"

class Mesh
{
    public:
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures;

    VAO vao;

    Mesh(std::vector <Vertex>& verts, std::vector <GLuint> &inds, std::vector <Texture> &texts);
    void draw(Shaders* shader, Camera* camera, glm::mat4 model, glm::vec3 defaultColor);
};

#endif