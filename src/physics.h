#ifndef PHYSICS_H
#define PHYSICS_H

#include"ball.h"
class PhysicsModule
{
    std::vector <glm::vec3> gravityPoints;
    std::vector <ingameObject*> objects;
    float borderOfDomain;
    glm::vec3 centerOfDomain;
    void applyForceGrav(ingameObject* object);
    void applyForceAeroDyn(ingameObject* object);
public:
    PhysicsModule() {};
    PhysicsModule(modelImporter* importer, Shaders* shaderprogram);
    void process(float fpsTime, Shaders* shaderProgram, Camera* camera);
    void addNewGravityCenter(glm::vec3 pos);
    bool gravity = false;
	bool aero = false;

};

#endif