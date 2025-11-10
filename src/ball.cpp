#include "ball.h"

glm::vec3 forceF(glm::vec3 R)
{
    float magnitude = glm::length(R);
    float epsilon = 0.2f;
    return -R/(float)(pow(magnitude* magnitude + epsilon*epsilon, 1.0f));
}


Ball::Ball(modelImporter *importer, glm::vec3 center, float size, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float border) : ingameObject("resources/models/ball/ball.obj", importer)
{
    this->center = center;
    this->border = border;
    this->mass = (size*size*size)/100.0f;
    this->model.scale = glm::vec3(0.01f,0.01f,0.01f)*size;
    this->model.translation = position;
	this->acc = forceF(this->model.translation - this->center)/mass;
    this->vel=velocity;
    this->model.defColor = color;
}

void Ball::process(float dt, Shaders& shader, Camera& camera)
{
	this->acc = forceF(this->model.translation - this->center)/mass;

    for (int i=0; i<3; i++)
    {
        if (this->model.translation[i] > center[i]+border)
        {
            this->vel[i] = -abs(this->vel[i]);
            this->model.translation[i] = (center[i]+border);
        }
        if (this->model.translation[i] < center[i]-border)
        {
            this->vel[i] = abs(this->vel[i]);
            this->model.translation[i] = (center[i]-border);
        }
    }

    ingameObject::process(dt, shader, camera);

}