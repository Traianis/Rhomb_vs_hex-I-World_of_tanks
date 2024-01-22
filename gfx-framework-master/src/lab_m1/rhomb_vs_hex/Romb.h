#pragma once

#include "components/simple_scene.h"
class Romb
{
   

public:
    Romb(float x, float y, float position, int type,float scale);
    Romb();
    float GetX();
    float GetY();
    int GetType();
    bool GetPosition();
    bool GetDie();
    float GetScale();
    int GetShoot();
    void SetX(float x);
    void SetY(float y);
    void SetType( int type);
    void SetPosition(bool position);
    void SetDie(bool die);
    void SetScale(float scale);
    void SetShoot(int shoot);
private:
    float x, y, scale;
    int type;
    bool die, position;
    int shoot;
};
