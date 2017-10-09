#include "Projectile.h"



Projectile::Projectile()
{
	this->velocity = this->init_velocity;
	this->y_velocity = this->init_velocity;
	this->position = glm::vec3(1.0f, 1.0f, 1.0f);
	std::cout << this->velocity << "velocity\n\n";
}


Projectile::~Projectile()
{
}

glm::vec3 Projectile::UpdatePosition(GLfloat delta_time, bool direction, GLfloat gradient)
{
	std::cout << this->velocity << "velocity\n\n";
	if (this->is_existing)
	{
		//this->position[0] += this->velocity * delta_time;
		//this->position[1] += this->velocity * delta_time;
		this->time += delta_time;
		if (this->velocity > 0)
			this->velocity -= this->decay * delta_time;
		else
			this->velocity = 0.0f;
		this->y_velocity -= this->decay * delta_time;
		this->position = glm::vec3(this->velocity * delta_time, 0.0f, 0.0f); //potential need to * delta_time
	}

	if (this->time > 2.0f)
	{
		std::cout << "object destroyed\n";
		this->is_existing = false;
	}

	return this->position;
}

void Projectile::FireBullet(GLfloat delta_time, bool direction, GLfloat gradient)
{
	this->position = this->UpdatePosition(delta_time, direction, gradient);
}