#include "lab_m1/rhomb_vs_hex/Enemy.h"

using namespace std;


Enemy::Enemy(float x, float y, float scale, bool toRand, int type)
{
	this->x = x;
	this->y = y;
	this->scale = scale;
	this->die = 0;
	this->life = 3;
	this->type = type;
	this->toRand = toRand;
}

Enemy::Enemy()
{

}


int Enemy::GetLife()
{
	return this->life;
}

bool Enemy::GetDie()
{
	return this->die;
}
float Enemy::GetX()
{
	return this->x;
}

float Enemy::GetY()
{
	return this->y;
}

bool Enemy::GetToRand()
{
	return this->toRand;
}

int Enemy::GetType()
{
	return this->type;
}

float Enemy::GetScale()
{
	return this->scale;
}

void Enemy::SetX(float x)
{
	this->x = x;
}

void Enemy::SetY(float y)
{
	this->y = y;
}

void Enemy::SetToRand(bool toRand)
{
	this->toRand = toRand;
}

void Enemy::SetType(int type)
{
	this->type = type;
}

void Enemy::SetScale(float scale)
{
	this->scale = scale;
}

void Enemy::SetDieOne()
{
	this->die = 1;
}

void Enemy::SetLife(int life)
{
	this->life = life;
}