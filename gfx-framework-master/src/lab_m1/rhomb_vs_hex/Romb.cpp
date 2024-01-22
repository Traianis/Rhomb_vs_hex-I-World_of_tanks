#include "lab_m1/rhomb_vs_hex/Romb.h"

using namespace std;


Romb::Romb(float x, float y, float position,int type, float scale)
{
	this->x = x;
	this->position = position;
	this->y = y;
	this->type = type;
	this->die = 0;
	this->scale = scale;
	this->shoot = 0;
}

Romb::Romb()
{

}



float Romb::GetX()
{
	return this->x;
}

float Romb::GetY()
{
	return this->y;
}

bool Romb::GetPosition()
{
	return this->position;
}

bool Romb::GetDie()
{
	return this->die;
}

int Romb::GetType()
{
	return this->type;
}

float Romb::GetScale()
{
	return this->scale;
}

int Romb::GetShoot()
{
	return this->shoot;
}

void Romb::SetX(float x)
{
	this->x = x;
}

void Romb::SetY(float y)
{
	this->y = y;
}

void Romb::SetPosition(bool position)
{
	this->position = position;
}

void Romb::SetType(int type)
{
	this->type= type;
}

void Romb::SetDie(bool die)
{
	this->die = die;
}

void Romb::SetScale(float scale)
{
	this->scale = scale;
}

void Romb::SetShoot(int shoot)
{
	this->shoot = shoot;
}