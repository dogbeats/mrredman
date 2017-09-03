#pragma once
#include <cmath>

#include "Object.h"
#include "Player.h"

class Collision
{
public:
	Collision();
	~Collision();
	bool DetectCollision(GLfloat player_hitbox_vertices[], glm::vec3 player_position);

private:
	bool LineIntersection(GLfloat hitbox_x1, GLfloat hitbox_y1, GLfloat hitbox_x2, GLfloat hitbox_y2, std::vector<GLfloat> player_hitbox_vertices, glm::vec3 player_position);
	bool Intersects(GLfloat hitbox_x1, GLfloat hitbox_y1, GLfloat hitbox_x2, GLfloat hitbox_y2, std::vector<GLfloat> player_hitbox_vertices, glm::vec3 player_position);
};

