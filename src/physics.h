#ifndef PHYSICS_H
#define PHYSICS_H

#include"ball.h"
class PhysicsModule
{

    std::vector <ingameObject*> objects;
    void applyForceGrav(ingameObject* object);
    void applyForceAeroDyn(ingameObject* object);
    public:
    PhysicsModule() {};
    PhysicsModule(modelImporter* importer, Shaders* shaderprogram);
    void process(float fpsTime, Shaders* shaderProgram, Camera* camera, bool* gravity, bool* aero);

};

#endif