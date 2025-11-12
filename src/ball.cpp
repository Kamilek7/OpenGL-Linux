#include "ball.h"

glm::vec3 forceF(glm::vec3 R)
{
    float magnitude = glm::length(R);
    float epsilon = 0.2f;
    return -R/(float)(pow(magnitude + epsilon, 3.0f));
}


Ball::Ball(modelImporter *importer, glm::vec3 center, float size, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float border) : ingameObject("resources/models/ball/ball.obj", importer)
{
    this->center = center;
    this->border = border;
    this->size = size;
    this->mass = (size*size*size)/100.0f;
    this->model.scale = glm::vec3(0.01f,0.01f,0.01f)*size;
    this->model.translation = position;
	this->acc = glm::vec3(0.0f,0.0f,0.0f);
    this->vel=velocity;
    this->model.defColor = color;
}

void Ball::process(float dt, Shaders& shader, Camera& camera, bool forces)
{
    if (forces)
	    this->acc = forceF(this->model.translation - this->center)/mass;
    else
        this->acc = glm::vec3(0.0f,0.0f,0.0f);
    for (int i=0; i<3; i++)
    {
        // Promien tej kuli wynosi 1.0 i jest skalowany przez size
        if (this->model.translation[i] + size > center[i]+border)
        {
            this->vel[i] = -this->vel[i];
            this->model.translation[i] = (center[i]+border) -size;
        }
        if (this->model.translation[i] - size < center[i]-border)
        {
            this->vel[i] = -this->vel[i];
            this->model.translation[i] = (center[i]-border) + size;
        }
    }

    ingameObject::process(dt, shader, camera, forces);

}