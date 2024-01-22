#pragma once

#include "lab_m1/rhomb_vs_hex/Romb.h"
#include "lab_m1/rhomb_vs_hex/Enemy.h"
#include "lab_m1/rhomb_vs_hex/Star.h"
#include <ctime>
#include <chrono>
#include "components/simple_scene.h"
using namespace std::chrono;

namespace m1
{
    class Main_r_h : public gfxc::SimpleScene
    {
     public:
         Main_r_h();
        ~Main_r_h();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void EnemyHit(std::vector<Star>& starsLine, std::vector <Romb>& rombsLine, int line, Enemy &enemy);
        void Shoot();
        void ShootStar(int i, std::vector<Star>& line);
        void EnemyAppear();
        bool DecreaseTotalPoints(int type);
        void RandomStars();
        void CadrRomb();
        void RombTypeRand(Romb &romb);
        void EnemyRand(float x, float y, float scx, float scy, int type);
        void RombRand(float x, float y, float scx, float scy, std::string star);
        void StarRand(float x, float y, float scx, float scy, float rotate, std::string sq);
        void SquareRand (float x, float y, std::string sq);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        float tx, ty;
        float dg;
        float sx, sy;

        std::vector<Romb> rombs;
        std::vector<Star> pointStars;
        std::vector<Star> totalStars;
        std::vector<Star> starLine1;
        std::vector<Star> starLine2;
        std::vector<Star> starLine3;
        std::vector<Enemy> enemyLine1;
        std::vector<Enemy> enemyLine2;
        std::vector<Enemy> enemyLine3;
        std::vector < int> totalLifes;
        int pointsUp,totalPoints;
        int ok;
        int picked;
        float line1, line2, line3;

        Romb pickedRomb;
        // TODO(student): If you need any other class variables, define them here.
        std::chrono::steady_clock::time_point start_time,current_time;
        std::chrono::seconds duration, duration_aux;
        int current_time_aux;
        float totalStarsX;
        float totalStarsY;

        int totalLife;
    };
}   // namespace m1
