#pragma once

#include "lab_m1/world_of_tanks/tank_transform3D.h"
#include "components/simple_scene.h"
class Proiectil
{


public:
    Proiectil(float x, float y, float z, float rotation, glm::mat4 matrix_tun_rot, int nr,bool my);
    Proiectil();
    glm::vec3 GetPos();
    glm::vec3 GetSc();
    glm::vec3 GetCol();
    glm::vec3 GetRealPos();

    glm::mat4 Rend();

    int Life();
    int GetLife();
    void Move(float deltaTime);

    bool my;
private:
    glm::mat4 matrix_tun_rot;
    glm::vec3 position, real_pos;
    glm::vec3 scale;
    glm::vec3 color;
    int life;
    float gYaw;
    float rotation;
};
