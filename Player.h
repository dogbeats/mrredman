#pragma once
#include "Render.h"
#include "Collision.h"
#include "MainGame.h"

class Player
{
public:
	Player();
	~Player();
	void DrawPlayer(bool loadedInitial, Shader ourShader);
	void PlayerAir(GLfloat total_delta_time);
	void PlayerJump();
	void MovePlayer(GLint key);
};

