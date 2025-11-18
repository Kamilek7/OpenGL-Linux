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
	virtual void process(float dt, Shaders& shader, Camera& camera, bool gravity, bool aero);
};
#endif