#include "lab_m1/world_of_tanks/Cladire.h"
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;


Cladire::Cladire()
{
	float x = std::rand() % 10;
	x += 5.f;
	float z = std::rand() % 10;
	z += 5.f;
	float x_scale = std::rand() % 4 + 1;
	x_scale *= 2;
	float y_scale = std::rand() % 12 + 3;
	float z_scale = std::rand() % 4 + 1;
	z_scale *= 2;

	int cadr = std::rand() % 4;
	switch (cadr)
	{
	case 0:
	{
		this->position = { x,y_scale / 2.f,z };
		break;
	}
	case 1:
	{
		this->position = { -x,y_scale / 2.f,z };
		break;
	}
	case 2:
	{
		this->position = { x,y_scale / 2.f,-z };
		break;
	}
	case 3:
	{
		this->position = { -x,y_scale / 2.f,-z };
		break;
	}
	default:
	{
		this->position = {0,0,0 };
		break;
	}
	}

	this->scale = { x_scale, y_scale, z_scale };
	this->color = { 111.f / 255.f, 216.f / 255.f, 242.f / 255.f };
}

glm::mat4 Cladire::Rend()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= tema_transform3D::Translate(this->position[0], this->position[1], this->position[2]);
	modelMatrix *= tema_transform3D::Scale(this->scale[0], this->scale[1], this->scale[2]);
	return modelMatrix;
}

glm::vec3 Cladire::GetPos()
{
	return this->position;
}

glm::vec3 Cladire::GetSc()
{
	return this->scale;
}

glm::vec3 Cladire::GetCol()
{
	return this->color;
}


