#ifndef OBJECT_H
#define OBJECT_H

#include "model.h"
class ingameObject
{
protected:
	float time;
	float mass;
	glm::vec3 acc;
	glm::vec3 vel;
	glModel model;

public:
	ingameObject(const char* name, modelImporter *importer);
	void applyForce(glm::vec3 force);
	void resetForce();
	glm::vec3 getVelocity();
	virtual void process(float dt, Shaders* shader, Camera* camera);
	virtual glm::vec3 getMagnitudeFromCenter(glm::vec3 center);
	virtual float getSize();
	virtual void checkCollisionWithDomain(glm::vec3 center, float border) {}
	
};
#endif