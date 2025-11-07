#ifndef BALL_H
#define BALL_H

#include "object.h"

class Ball : public ingameObject
{
    glm::vec3 center;
    // Ograniczenie zakłoceń spowodowanych wykorzystaniem modelu matematycznego
    float epsilon = 0.1f;
    public:
    Ball(modelImporter *importer, glm::vec3 center, float size, glm::vec3 position, glm::vec3 velocity);
    void process(float dt, Shaders& shader, Camera& camera);
};

#endif