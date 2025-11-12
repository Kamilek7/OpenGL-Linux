#ifndef BALL_H
#define BALL_H

#include "object.h"

class Ball : public ingameObject
{
    glm::vec3 center;
    // Ograniczenie zakłoceń spowodowanych wykorzystaniem modelu matematycznego
    float border;
    public:
    Ball(modelImporter *importer, glm::vec3 center, float size, glm::vec3 position, glm::vec3 velocity,glm::vec3 color, float border);
    void process(float dt, Shaders& shader, Camera& camera, bool forces);
};

#endif