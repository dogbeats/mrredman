#pragma once
#include "Render.h"
#include "Collision.h"
#include "MainGame.h"
#include "Projectile.h"

class Player
{
public:
	Player();
	~Player();
	void DrawPlayer(bool loadedInitial, Shader ourShader);
	void PlayerAir(GLfloat total_delta_time);
	void PlayerJump();
	void MovePlayer(GLint key, GLfloat total_delta_time);
	void EndMovement();
	void StartMovement(GLint key);
	glm::vec3 GetPlayerPosition();
	void RotateArms(double mouse_x, double mouse_y);
	void FireBullet();

private:	
	void UpdateXVelocity(GLint direction, GLfloat total_delta_time);
	void UpdatePlayerPosition();
};

