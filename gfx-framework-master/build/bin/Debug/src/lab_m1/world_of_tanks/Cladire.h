#pragma once

#include "lab_m1/world_of_tanks/tank_transform3D.h"
#include "components/simple_scene.h"
class Cladire
{


public:
    Cladire();

    glm::vec3 GetPos();
    glm::vec3 GetSc();
    glm::vec3 GetCol();

    glm::mat4 Rend();
private:
    glm::mat4 modelMatrix;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 color;
    glm::vec3 tar;

    int shoot;
    float gYaw;
};
