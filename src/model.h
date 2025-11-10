#ifndef MODEL_H
#define MODEL_H

#include "importer.h"


class glModel
{
public:
	glModel() {};
	glModel(const char* filer, modelImporter* importer);
	void draw(Shaders& shader, Camera& camera);
	glm::mat4 getMatrix();
	// w razie gdyby tekstury nie dzialaly
	glm::vec3 defColor;
	std::vector<Mesh> meshes;
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
};
#endif