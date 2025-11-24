#include "physics.h"

void PhysicsModule::applyForceGrav(ingameObject* object)
{
    float magnitude = glm::length(object->getMagnitudeFromCenter());
    float epsilon = 0.2f;
	object->applyForce(-object->getMagnitudeFromCenter()/(float)(pow(magnitude + epsilon, 3.0f)));
}

void PhysicsModule::applyForceAeroDyn(ingameObject* object)
{
    float mu = 0.0001f;
    object->applyForce(-6.0f*object->getVelocity()*mu*object->getSize()*(float)(std::numbers::pi));
}

PhysicsModule::PhysicsModule(modelImporter* importer, Shaders* shaderProgram)
{
    int randCount = 50;
	float offset = -10.0f;
	float border = 4.0f;

	float division = (float)(randCount/2)/(border-0.1f);
	float speedDiv = 45.0f;
	glUniform3f(glGetUniformLocation(shaderProgram->getID(), "lightPos"), 0.0f, 0.0f, offset);
	
	for (int i=0; i<1000;i++)
	{

		objects.push_back(new Ball(importer, glm::vec3(0.0f,0.0f,offset), (rand()%randCount)/10.0f + 0.3, glm::vec3((rand()%randCount-randCount/2)/division,(rand()%randCount-randCount/2)/division,offset+ (rand()%randCount-randCount/2)/division), glm::vec3((1-2*rand()%2)*(rand()%randCount+1)/speedDiv, (1-2*rand()%2)*(rand()%randCount+1)/speedDiv,(1-2*rand()%2)*(rand()%randCount+1)/speedDiv),glm::vec3((rand()%255)/255.0f, (rand()%255)/255.0f,(rand()%255)/255.0f), border));
	}
}
void PhysicsModule::process(float fpsTime, Shaders* shaderProgram, Camera* camera, bool* gravity, bool* aero)
{
    for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->resetForce();
		if (*gravity)
			this->applyForceGrav(objects[i]);
		if (*aero)
			this->applyForceAeroDyn(objects[i]);
		objects[i]->process(fpsTime, shaderProgram, camera);
	}
}