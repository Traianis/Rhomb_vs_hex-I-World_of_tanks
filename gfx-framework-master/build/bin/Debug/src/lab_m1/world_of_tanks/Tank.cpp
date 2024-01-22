#include "lab_m1/world_of_tanks/Tank.h"
#include "lab_m1/world_of_tanks/Cladire.h"
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

Tank::Tank(bool e)
{
	float x = std::rand() % 10 + 20;
	float z = std::rand() % 10 + 20;
	int cadr = std::rand()%4;
	switch (cadr)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			x = -x;
			break;
		}
		case 2:
		{
			x = -x;
			z = -z;
			break;
		}
		case 3:
		{
			z = -z;
			break;
		}
		default:
		{
			break;
		}
	}

	this->corp_position = { 0 + x, 0.8f, 0.046f + z };
	this->corp_scale = { 3.8f, 3.7f, 3.5f };
	this->corp_color = { 0, 1, 0 };
	this->senile_scale = { 3.4f, 3, 3.05f };
	this->senile_position = { 0 + x, 0.6f, 0 + z };
	this->senile_color = { 129.f / 255.f, 130.f / 255.f, 125.f / 255.f };
	this->tun_position = { 0 + x, 0, 0 + z };
	this->tun_scale = { 23, 8, 8 };
	this->tun_color = { 1,0,0 };
	this->turela_position = { 0 + x, 1.4f, 0 + z };
	this->turela_scale = { 3.5f, 3.5f, 3.5f };
	this->turela_color = { 0.2f, 0.5f, 1 };
	rotation = 3.14f / 1.8f;
	x_move = 0;
	z_move = 0;
	matrix_tun_rot = glm::mat4(1) * tema_transform3D::RotateOY(rotation);
	tun_rot = rotation;
	shoot = 0;
	life = 3;
	rot_sec = -1;
	move_sec = 1;
}

Tank::Tank()
{
	// Am dat valori pana cand le am asezat bine
	this->corp_position = { 0, 0.8f, 0.046f };
	this->corp_scale = { 3.8f, 3.7f, 3.5f };
	this->corp_color = { 0, 1, 0 };
	this->senile_scale = { 3.4f, 3, 3.05f };
	this->senile_position = { 0, 0.6f, 0 };
	this->senile_color = { 129.f / 255.f, 130.f / 255.f, 125.f / 255.f };
	this->tun_position = { 0, 0, 0 };
	this->tun_scale = {	23, 8, 8};
	this->tun_color = { 1,0,0 };
	this->turela_position = { 0, 1.4f, 0 };
	this->turela_scale = { 3.5f, 3.5f, 3.5f };
	this->turela_color = { 0.2f, 0.5f, 1 };
	rotation = 3.14f / 1.8f;
	tun_rot = rotation;
	x_move = 0;
	z_move = 0;
	this->shoot = 0;
	this->life = 3;
}

glm::vec3 Tank::GetForwardVector()
{
	glm::vec4 forwardVector = glm::rotate(glm::mat4(1.0f), this->rotation, glm::vec3(0, 1, 0)) * glm::vec4(-1, 0, 0, 1);

	return glm::normalize(glm::vec3(forwardVector));
}

void Tank::Tun_rot(float x, float z)
{
	glm::vec3 pos = this->corp_position;
	pos[0] += x_move;
	pos[2] += z_move;
	glm::vec3 tragetVec = glm::normalize(glm::vec3(x, 0.8f, z) - pos);
	glm::quat rotQuat = glm::rotation(glm::vec3(-1, 0, 0), tragetVec);
	matrix_tun_rot = glm::toMat4(rotQuat);
	
}

void Tank::Mouse_move(float deltaX, float sensivityOX, bool left_right)
{
	if (left_right)
		tun_rot -= deltaX * sensivityOX;
	else
		tun_rot -= deltaX * sensivityOX;
}

glm::vec3 Tank::GetRealPos()
{
	glm::vec3 real_pos = { 0,0,0 };
	return real_pos;
}

Proiectil Tank::Shoot_pro(int nr)
{
	Proiectil new_pro;
	if (this->shoot == 0)
	{
		if (nr == 2)
		{
			this->shoot = nr;
			new_pro = Proiectil(this->tun_position[0] + x_move, this->tun_position[1], this->tun_position[2] + z_move, this->tun_rot, glm::mat4(1), 5., 1);
		}
		else
		{
			this->shoot = nr;
			float cosinus_a = 0;
			new_pro = Proiectil(this->tun_position[0] + x_move, this->tun_position[1], this->tun_position[2] + z_move, cosinus_a, this->matrix_tun_rot, 3, 0);
		}
		this->ResetShoot(nr);
	}
	return new_pro;
}

void Tank::Dcr_shoot()
{
	if (shoot)
		shoot--;
}

void Tank::ResetShoot(int nr)
{
	this->shoot = nr;
}

void Tank::W_move(float deltaTime)
{
	float ung = glm::degrees(this->rotation);
	ung = std::min(std::max(ung,1.f), 359.f);

	this->x_move = this->x_move + glm::sin(ung + 4.712f) * 2*deltaTime;// Am dat valori pana cand a mers in directia buna
	this->z_move = this->z_move + glm::cos(ung + 4.712f) * 2*deltaTime;// Am dat valori pana cand a mers in directia buna
	
}

void Tank::S_move(float deltaTime)
{
	float ung = glm::degrees(this->rotation);
	ung = std::min(std::max(ung, 1.f), 359.f);
	this->x_move = this->x_move - glm::sin(ung + 4.712f) * 2 * deltaTime;// Am dat valori pana cand a mers in directia buna
	this->z_move = this->z_move - glm::cos(ung + 4.712f) * 2 * deltaTime;// Am dat valori pana cand a mers in directia buna
}

void Tank::A_rotation(float deltaTime)
{
	this->rotation += deltaTime * 0.01f;
	tun_rot += deltaTime * 0.01f;
}


void Tank::D_rotation(float deltaTime)
{
	this->rotation -= deltaTime * 0.01f;
	tun_rot -= deltaTime * 0.01f;

}

void Tank::Center_move(float x, glm::vec3 dir)
{
	x_move += dir.x * x;
	z_move += dir.z * x;
}

glm::mat4 Tank::Turela_rend(bool my)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= tema_transform3D::Translate(this->turela_position[0] + x_move, this->turela_position[1], this->turela_position[2] + z_move);
	modelMatrix *= tema_transform3D::Scale(this->turela_scale[0], this->turela_scale[1], this->turela_scale[2]);
	if (my)
		modelMatrix *= tema_transform3D::RotateOY(this->tun_rot);
	else 
		modelMatrix *= matrix_tun_rot;
	return modelMatrix;
}

glm::mat4 Tank::Tun_rend(bool my)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= tema_transform3D::Translate(this->tun_position[0] + x_move, this->tun_position[1], this->tun_position[2] + z_move);
	if (my)
		modelMatrix *= tema_transform3D::RotateOY(this->tun_rot);
	else 
		modelMatrix *= matrix_tun_rot;
	modelMatrix *= tema_transform3D::Translate(-2, 1.3f, 0);
	modelMatrix *= tema_transform3D::Scale(this->tun_scale[0], this->tun_scale[1], this->tun_scale[2]);

	return modelMatrix;
}

glm::mat4 Tank::Corp_rend()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= tema_transform3D::Translate(this->corp_position[0] + x_move, this->corp_position[1], this->corp_position[2] + z_move);
	modelMatrix *= tema_transform3D::Scale(this->corp_scale[0], this->corp_scale[1], this->corp_scale[2]);
	modelMatrix *= tema_transform3D::RotateOY(this->rotation);
	return modelMatrix;
}

glm::mat4 Tank::Senile_rend()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= tema_transform3D::Translate(this->senile_position[0] + x_move, this->senile_position[1], this->senile_position[2]+z_move);
	modelMatrix *= tema_transform3D::Scale(this->senile_scale[0], this->senile_scale[1], this->senile_scale[2]);
	modelMatrix *= tema_transform3D::RotateOY(this->rotation);
	return modelMatrix;
}


glm::vec3 Tank::GetTurela_col()
{
	return this->turela_color;
}

glm::vec3 Tank::GetTun_col()
{
	return this->tun_color;
}

glm::vec3 Tank::GetCorp_col()
{
	return this->corp_color;
}

glm::vec3 Tank::GetSenile_col()
{
	return this->senile_color;
}


glm::vec3 Tank::GetTun_pos()
{
	return this->tun_position;
}

glm::vec3 Tank::GetTun_sc()
{
	return this->tun_scale;
}

glm::vec3 Tank::GetTurela_pos()
{
	return this->turela_position;
}

glm::vec3 Tank::GetTurela_sc()
{
	return this->turela_scale;
}

glm::vec3 Tank::GetSenile_pos()
{
	return this->senile_position;
}

glm::vec3 Tank::GetSenile_sc()
{
	return this->senile_scale;
}

glm::vec3 Tank::GetCorp_pos()
{
	return this->corp_position;
}

glm::vec3 Tank::GetCorp_sc()
{
	return this->corp_scale;
}

int Tank::GetShoot()
{
	return this->shoot;
}


