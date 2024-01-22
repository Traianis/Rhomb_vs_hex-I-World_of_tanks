#pragma once

#include "lab_m1/world_of_tanks/tank_transform3D.h"
#include "lab_m1/world_of_tanks/Proiectil.h"
#include "components/simple_scene.h"
class Tank
{


public:
    float rotation, x_move, z_move;
    Tank();
    Tank(bool e);
    glm::vec3 GetTurela_pos();
    glm::vec3 GetTun_pos();
    glm::vec3 GetSenile_pos();
    glm::vec3 GetCorp_pos();
    glm::vec3 GetTurela_sc();
    glm::vec3 GetTun_sc();
    glm::vec3 GetCorp_sc();
    glm::vec3 GetSenile_sc();
    glm::vec3 GetTurela_col();
    glm::vec3 GetTun_col();
    glm::vec3 GetCorp_col();
    glm::vec3 GetSenile_col();
    
    Proiectil Shoot_pro(int nr);

    int GetShoot();
    void ResetShoot(int nr);
    void Dcr_shoot();

    void Center_move(float x, glm::vec3 dir);
    void Tun_rot(float x, float z);
    void Mouse_move(float deltaX, float sensivityOX, bool left_right);

    void A_rotation(float deltaTime);
    void D_rotation(float deltaTime);

    void W_move(float deltatime);
    void S_move(float deltatime);

    glm::mat4 Turela_rend(bool my);
    glm::mat4 Tun_rend(bool my);
    glm::mat4 Corp_rend();
    glm::mat4 Senile_rend();

    glm::vec3 GetRealPos();
    glm::vec3 GetForwardVector();
    
    int rot_sec, move_sec;
    glm::mat4 matrix_tun_rot;
    float tun_rot;
    bool a;
    int shoot, life;
private:

    glm::vec3 tun_position, turela_position, corp_position, senile_position;
    glm::vec3 tun_scale, turela_scale, corp_scale, senile_scale;
    glm::vec3 tun_color, turela_color, corp_color, senile_color;
};
