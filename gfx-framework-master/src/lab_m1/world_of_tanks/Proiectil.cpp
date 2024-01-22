#include "lab_m1/world_of_tanks/Proiectil.h"
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

Proiectil::Proiectil(float x, float y, float z, float rotation, glm::mat4 matrix_tun_rot, int nr, bool my)
{
	this->position = { x, y, z };
	this->scale = { 0.7f, 0.7f, 0.7f };
	this->color = { 253.f / 255.f, 108.f / 255.f, 158.f / 255.f };
	this->matrix_tun_rot = matrix_tun_rot;
	this->rotation = rotation;
	this->my = my;
	gYaw = 0;
	life = nr;
}


Proiectil::Proiectil()
{
	life = -1;
}

int Proiectil::Life()
{
	this->life--;
	return this->life;
}

void Proiectil::Move(float deltaTime)
{	

	float ung = glm::degrees(this->rotation);
	ung = std::min(std::max(ung, 1.f), 359.f);

	if (my)
	//mytank shoot
	{
		this->position[0] = this->position[0] + glm::sin(ung + 4.7f) * deltaTime * 10;
		this->position[2] = this->position[2] + glm::cos(ung + 4.7f) * deltaTime * 10;
	}
	else
	//enemy shoot
	{
		this->position[0] = this->position[0] - (matrix_tun_rot[0][0]) * deltaTime * 10;
		this->position[2] = this->position[2] - (matrix_tun_rot[0][2]) * deltaTime * 10;
	}

}

glm::mat4 Proiectil::Rend()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= tema_transform3D::Translate(this->position[0], this->position[1], this->position[2]);
	if (my)
		modelMatrix *= tema_transform3D::RotateOY(this->rotation);
	else 	
		modelMatrix *= matrix_tun_rot;
	modelMatrix *= tema_transform3D::Translate(-3.64f, 1.3f, 0);
	modelMatrix *= tema_transform3D::Scale(this->scale[0], this->scale[1], this->scale[2]);
	return modelMatrix;
}

glm::vec3 Proiectil::GetPos()
{
	return this->position;
}

glm::vec3 Proiectil::GetSc()
{
	return this->scale;
}

glm::vec3 Proiectil::GetCol()
{
	return this->color;
}

glm::vec3 Proiectil::GetRealPos()
{
	float x = -3.64f, y = 1.3f, z=0;
	if (my)
	{
		z = -glm::sin(glm::degrees(this->rotation)) * x;
		x = glm::cos(glm::degrees(this->rotation)) * x;
	}
	else
	{
		z = (matrix_tun_rot[0][2]) * x;
		x = matrix_tun_rot[0][0] * x;
	}
	x += position[0];
	y += position[1];
	z += position[2];
	glm::vec3 real_pos = { x,y,z };
	return real_pos;
}

int Proiectil::GetLife()
{
	return this->life;
}

