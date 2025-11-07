#include "ball.h"

Ball::Ball(modelImporter *importer, glm::vec3 center, float size, glm::vec3 position, glm::vec3 velocity) : ingameObject("resources/models/ball/ball.obj", importer)
{
    this->center = center;
    this->epsilon = 0.2f;
    this->mass = size*size*size;
    this->model.scale = glm::vec3(0.01f,0.01f,0.01f)*size;
    this->model.translation = position;
    float magnitude = glm::length(this->model.translation - center);
	this->acc = -(this->model.translation - center)/(float)(pow(magnitude* magnitude + epsilon*epsilon, 3/2.f));
    this->vel=velocity;
}

void Ball::process(float dt, Shaders& shader, Camera& camera)
{
	float magnitude = glm::length(this->model.translation - this->center);
	this->acc = -(this->model.translation - this->center)/(float)(pow(magnitude* magnitude + epsilon*epsilon, 3/2.f));
    ingameObject::process(dt, shader, camera);
}