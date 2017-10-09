#pragma once

#include "MainGame.h"

class Projectile
{
public:
	Projectile();
	~Projectile();

	bool is_existing = true;	
	glm::vec3 position;
	GLfloat gradient;

	void FireBullet(GLfloat delta_time, bool direction, GLfloat gradient);

private:
	GLfloat texture_coordinates[2];

	GLfloat velocity, init_velocity = 10.5f, decay = 0.0f, y_velocity, time;

	glm::vec3 UpdatePosition(GLfloat delta_time, bool direction, GLfloat gradient);
};

