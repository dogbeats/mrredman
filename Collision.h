#pragma once
#include <cmath>

#include "Object.h"
#include "Player.h"

class Collision
{
public:
	Collision();
	~Collision();
	GLfloat * DetectWall(GLfloat player_hitbox_vertices[], glm::vec3 player_position, GLfloat player_movement[2], GLint player_direction, GLfloat player_movement_speed);
	GLfloat * DetectCollision(GLfloat player_hitbox_vertices[], glm::vec3 player_position, bool is_player_falling, GLfloat player_speed);

private:
	GLfloat * LineIntersection(GLfloat hitbox_x1, GLfloat hitbox_y1, GLfloat hitbox_x2, GLfloat hitbox_y2, std::vector<GLfloat> player_hitbox_vertices, glm::vec3 player_position, GLfloat player_speed);
};

