#pragma once

#include "components/simple_scene.h"
#include "lab_m1/world_of_tanks/tank_camera.h"
#include "lab_m1/world_of_tanks/Tank.h"
#include "lab_m1/world_of_tanks/Cladire.h"
#include "lab_m1/world_of_tanks/Proiectil.h"
#include "lab_m1/world_of_tanks/tank_transform3D.h"
#include <ctime>
#include <chrono>
using namespace std::chrono;

namespace m1
{
    class Main_wot : public gfxc::SimpleScene
    {
    public:
        Main_wot();
        ~Main_wot();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void Tank_shoot();
        void Coliz_tank_tank();
        void Coliz_tank_build();
        bool Coliz_proj(int n);
        void EnemyTank_move();
        void Projectiles_life();
        void Tank_in_radius();
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, int life);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::TemaCamera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float length, width, radians, znear, zfar;
        bool perspective, ortho;
        std::chrono::steady_clock::time_point start_time, current_time;
        std::chrono::seconds duration_aux;

        Tank MyTank, EnemyTank;
        std::vector<Proiectil> projectiles;
        std::vector<Cladire> buildings;

        int finish_time_sec;
        float mouse_x, mouse_y;

        bool d_3;
        int total_points = 0, finish_game;
    };
}   // namespace m1
