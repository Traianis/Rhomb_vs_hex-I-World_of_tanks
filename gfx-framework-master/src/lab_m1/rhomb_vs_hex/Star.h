#pragma once

#include "components/simple_scene.h"
class Star
{


public:
    Star(float x, float y,float scale,bool toRand);
    Star(float x, float y, float scale, float rotate, std::string star, int type);
    Star();
    float GetX();
    float GetY();
    int GetType();
    float GetScale();
    float GetRotate();
    bool GetToRand();
    std::string GetStar();
    void SetX(float x);
    void SetY(float y);
    void SetType(int type);
    void SetToRand(bool toRand);
    void SetScale(float scale);
    void SetStar(std::string star);
    void SetRotate(float rotate);

    void Rotate(float deltaTime);
    void Move(float deltaTime);
private:
    float x, y, scale, rotate;
    int type;
    bool die;
    bool toRand;//to be randed
    std::string star;
};
