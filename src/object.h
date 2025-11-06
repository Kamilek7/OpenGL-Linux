#ifndef OBJECT_H
#define OBJECT_H

#include "model.h"
class ingameObject
{
	float time;
	glModel model;

public:
	ingameObject(const char* name, modelImporter *importer);
	void process(float dt, Shaders& shader, Camera& camera);
};
#endif