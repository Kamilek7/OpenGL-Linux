#include "ball.h"

glm::vec3 forceGrav(glm::vec3 R)
{
    float magnitude = glm::length(R);
    float epsilon = 0.2f;
    return -R/(float)(pow(magnitude + epsilon, 3.0f));
}

glm::vec3 forceAeroDyn(glm::vec3 vel, float R)
{
    float mu = 0.0001f;
    glm::vec3 temp = -6.0f*vel*mu*R*(float)(M_PI);
    return temp;
}


Ball::Ball(modelImporter *importer, glm::vec3 center, float size, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float border) : ingameObject("resources/models/ball/ball.obj", importer)
{
    this->center = center;
    this->border = border;
    this->size = size;
    this->mass = (size*size*size)/1000.0f;
    this->model.scale = glm::vec3(0.01f,0.01f,0.01f)*size;
    this->model.translation = position;
	this->acc = glm::vec3(0.0f,0.0f,0.0f);
    this->vel=velocity;
    this->model.defColor = color;
}

void Ball::process(float dt, Shaders& shader, Camera& camera, bool gravity, bool aero)
{
    this->acc = glm::vec3(0.0f,0.0f,0.0f);
    if (gravity)
        this->acc += forceGrav(this->model.translation - this->center)/mass;
    if (aero)
        this->acc += forceAeroDyn(this->vel, this->size)/mass;

    for (int i=0; i<3; i++)
    {
        // Promien tej kuli wynosi 0.01 i jest skalowany przez size
        if (this->model.translation[i] + size*0.01f > center[i]+border)
        {
            this->model.translation[i] = (center[i]+border) -size*0.01f;
            vel[i] = -vel[i];
        }
        if (this->model.translation[i] - size*0.01f < center[i]-border)
        {
            this->model.translation[i] = (center[i]-border) + size*0.01f;
            vel[i] = -vel[i];
        }
    }

    ingameObject::process(dt, shader, camera, gravity, aero);

}