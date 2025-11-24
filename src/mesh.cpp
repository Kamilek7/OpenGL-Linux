#include "mesh.h"

Mesh::Mesh(std::vector <Vertex>& verts, std::vector <GLuint> &inds, std::vector <Texture> &texts)
{
    vertices = verts;
    indices = inds;
    textures= texts;
    
    vao.bind();
    VBO vbo(vertices);
    EBO ebo(indices);
    vao.linkAttributes(vbo,0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0));
    vao.linkAttributes(vbo,1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(float)));
    vao.linkAttributes(vbo,2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6*sizeof(float)));
    vao.linkAttributes(vbo,3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9*sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

void Mesh::draw(Shaders* shader, Camera* camera, glm::mat4 matrix, glm::vec3 defaultColor)
{
    shader->useShader();
    vao.bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i=0; i<textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].type;
        if (type=="diffuse")
        {
            num = std::to_string(numDiffuse);
            numDiffuse++;
        }
        else if (type=="specular")
        {
            num = std::to_string(numSpecular);
            numSpecular++;
            
        }
        textures[i].texUnit(shader, (type+num).c_str(),i);
        textures[i].bind();
    }

    glUniform3f(glGetUniformLocation(shader->getID(), "generatedColor"), defaultColor.x, defaultColor.y, defaultColor.z);
    glUniform3f(glGetUniformLocation(shader->getID(), "camPos"), camera->position.x, camera->position.y, camera->position.z);
    camera->matrix(shader, "camMatrix");
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}