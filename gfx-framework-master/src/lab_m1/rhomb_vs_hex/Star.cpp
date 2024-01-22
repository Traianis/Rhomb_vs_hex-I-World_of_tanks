#include "lab_m1/rhomb_vs_hex/Star.h"

using namespace std;


Star::Star(float x, float y, float scale,bool toRand)
{
	this->x = x;
	this->y = y;
	this->scale = scale;
	this->die = 0;
	this->toRand = toRand;
}

Star::Star(float x, float y, float scale, float rotate, std::string star,int type)
{
	this->x = x;
	this->y = y;
	this->scale = scale;
	this->die = 0;
	this->star = star;
	this->rotate = rotate;
	this->type = type;
}

Star::Star()
{

}

void Star::Rotate(float deltaTime)
{
	this->rotate -= deltaTime * 0.1f;
	if (this->rotate == 0)
		this->rotate = 360;
}

void Star::Move(float deltaTime)
{
	this->x += 50 * deltaTime;
}

float Star::GetX()
{
	return this->x;
}

float Star::GetY()
{
	return this->y;
}

bool Star::GetToRand()
{
	return this->toRand;
}

int Star::GetType()
{
	return this->type;
}

float Star::GetScale()
{
	return this->scale;
}
float Star::GetRotate()
{
	return this->rotate;
}

std::string Star::GetStar()
{
	return this->star;
}
void Star::SetX(float x)
{
	this->x = x;
}

void Star::SetY(float y)
{
	this->y = y;
}

void Star::SetToRand(bool toRand)
{
	this->toRand = toRand;
}

void Star::SetType(int type)
{
	this->type = type;
}

void Star::SetScale(float scale)
{
	this->scale = scale;
}

void Star::SetStar(std::string star)
{
	this->star = star;
}

void Star::SetRotate(float rotate)
{
	this->rotate = rotate;
}