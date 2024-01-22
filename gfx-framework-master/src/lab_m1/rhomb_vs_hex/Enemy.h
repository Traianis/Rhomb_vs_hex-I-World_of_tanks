#pragma once

#include "components/simple_scene.h"
class Enemy
{


public:
    Enemy::Enemy(float x, float y, float scale, bool toRand, int type);
    Enemy();
    float GetX();
    float GetY();
    int GetType();
    float GetScale();
    bool GetToRand();
    bool GetDie();
    int GetLife();

    void SetX(float x);
    void SetY(float y);
    void SetType(int type);
    void SetToRand(bool toRand);
    void SetScale(float scale);
    void SetDieOne();
    void SetLife(int life);
private:
    float x, y, scale;
    int type, life;
    bool die;
    bool toRand;//to be randed
};
