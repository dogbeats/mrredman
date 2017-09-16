#include "Player.h"

GLuint VAO_p, VBO_p, VAO_p_hitbox, VBO_p_hitbox;

GLfloat player_vertices[] = {
	0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //bottom left
	-0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //bottom right
	0.25f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //top left
	-0.25f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, //top right
	-0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //bottom right
	0.25f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //bottom left
};

GLfloat player_hitbox_vertices[] = {
	0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, //0
	-0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f,
	-0.25f, 1.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 1.0f, //2
	-0.25f, -0.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 1.0f,
	-0.25f, -0.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, //4
	0.25f, -0.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f,
	0.25f, -0.0f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, //6
	0.25f, 1.0f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f
};

glm::vec3 player_position = glm::vec3(2.5f,  8.0f, 0.0f);

GLuint texture;
GLfloat player_delta_time = 0.0f;

bool player_jump = false;

//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Player::Player()
{
}


Player::~Player()
{
}

Collision collision;
GLfloat *player_on_ground;
GLfloat player_collision_line_data[3] = { 0, 0, 1 };
bool is_player_falling = true; //to be moved and determined in game - set as true for collision testing purposes
GLfloat y_acceleration = 0.0f, time_since_jump_fall = 1.0f;
GLfloat player_movement_speed[2] = { -0.1f, -0.1f };

glm::vec3 Player::GetPlayerPosition()
{
	return player_position;
}

void Player::PlayerAir(GLfloat total_delta_time)
{
	player_delta_time += total_delta_time;	
	
	if (!player_jump)
	{
		if (is_player_falling && player_delta_time > 0.0167f)
		{
			if(y_acceleration < 0.2f)
				y_acceleration = 0.05f * ((time_since_jump_fall - 1.0f)/2 + 1.0f);

			time_since_jump_fall += player_delta_time;

			player_on_ground = collision.DetectCollision(player_hitbox_vertices, player_position, is_player_falling, player_movement_speed[1]);

			if (player_on_ground[2] == 1)
			{
				is_player_falling = true;
				player_position[1] -= y_acceleration;
			}
			else if (player_on_ground[0] >= -1.0f && player_on_ground[0] <= 1.0f)
			{
				is_player_falling = false;

				if (player_on_ground[0] == 0)
					player_position[1] = player_on_ground[1];
				else
					player_position[1] = player_on_ground[0] * player_position[0] + player_on_ground[1];

//std::cout << " y = " << player_on_ground[0] << "x + " << player_
			}
			else
			{//CHECK THIS OPLACES

				if (player_on_ground[0] > 0)
					player_position[0] -= 0.1f;
				else
					player_position[0] += 0.1f;

				GLfloat temp_c_2 = player_position[1] - player_position[0] * player_on_ground[0]; // needs to be replaced with something "proper" -> player_on_ground[1] c value incorrect?

				//std::cout << player_position[0] << " " << player_position[1] << "   p_o_g 1 and 2 " << player_on_ground[0] << " " << player_on_ground[1] << " " << player_on_ground[2] << "\n";

				player_position[1] = player_position[0] * player_on_ground[0] + temp_c_2;

			}

			player_collision_line_data[0] = player_on_ground[0];
			player_collision_line_data[1] = player_on_ground[1];
			player_collision_line_data[2] = player_on_ground[2]; //checks if m = inf
			player_delta_time = 0.0f;
		}
	}
	else if (player_delta_time > 0.0167f)
	{
		y_acceleration -= 0.05f * time_since_jump_fall;
		time_since_jump_fall += player_delta_time;

		if (y_acceleration < 0.01f)
		{
			y_acceleration = 0.0f;
			player_jump = false;
			time_since_jump_fall = 1.0f;
			is_player_falling = true;
		}

		player_position[1] += y_acceleration;

		player_delta_time = 0.0f;
	}

	if (!is_player_falling && !player_jump)
	{
		time_since_jump_fall = 1.0f;
		y_acceleration = 0.0f;
	}
}

void Player::PlayerJump()
{
	if (!is_player_falling)
	{
		player_jump = true;
		time_since_jump_fall = 1.0f;
		y_acceleration = 0.9f;
	}
}

void Player::MovePlayer(GLint key)
{
	GLfloat dist_to_corner;
	GLfloat * can_move_in_direction;

	/*
		0 = MOVE LEFT
		1 = MOVE RIGHT
	*/
	if (key == 0)
	{
		can_move_in_direction = 0;
		can_move_in_direction = collision.DetectWall(player_hitbox_vertices, player_position, player_movement_speed, 0, -0.1f);

		if (can_move_in_direction[0] == 1)
		{
			std::cout << player_collision_line_data[0] << " " << player_collision_line_data[1] << " ";

			if (is_player_falling || player_jump)
			{
				player_position[0] -= 0.1f;
				//player_position[1] -= 0.1f;
			}
			else if (can_move_in_direction[1] < 0.0f && can_move_in_direction[1] >= -1.0f)
			{
				player_collision_line_data[0] = can_move_in_direction[1];
				player_collision_line_data[1] = can_move_in_direction[2];
				player_position[0] -= 0.1f;
				player_position[1] = player_position[0] * player_collision_line_data[0] + player_collision_line_data[1];
			}

			else
			{
				std::cout << "fdsfd \n\n move: ";
				std::cout << player_collision_line_data[0] << "  " << player_collision_line_data[1] << "\n\n";
				player_position[0] -= 0.1f;
				//dist_to_corner = 0.70711;
				player_position[1] = player_position[0] * player_collision_line_data[0] + player_collision_line_data[1];
			}
		}	
		else if (can_move_in_direction[0] == -1)
		{
			std::cout << "\nfalling\n";
			player_position[0] -= 0.1f;
			is_player_falling = true;
		}

	}

	if (key == 1)
	{
		can_move_in_direction = 0;
		can_move_in_direction = collision.DetectWall(player_hitbox_vertices, player_position, player_movement_speed, 0, 0.1f);

		if (can_move_in_direction[0] == 1)
		{
			std::cout << player_collision_line_data[0] << " " << player_collision_line_data[1] << " ";

			if (is_player_falling || player_jump)
			{
				player_position[0] += 0.1f;
				//player_position[1] -= 0.1f;
			}
			else if (can_move_in_direction[1] < 1.0f && can_move_in_direction[1] >= 0.0f)
			{
				player_collision_line_data[0] = can_move_in_direction[1];
				player_collision_line_data[1] = can_move_in_direction[2];
				player_position[0] += 0.1f;
				player_position[1] = player_position[0] * player_collision_line_data[0] + player_collision_line_data[1];
			}

			else
			{
				std::cout << "fdsfd \n\n move: ";
				std::cout << player_collision_line_data[0] << "  " << player_collision_line_data[1] << "\n\n";
				player_position[0] += 0.1f;
				//dist_to_corner = 0.70711;
				player_position[1] = player_position[0] * player_collision_line_data[0] + player_collision_line_data[1];
			}
		}
		else if (can_move_in_direction[0] == -1)
		{
			std::cout << "\nfalling\n";
			player_position[0] += 0.1f;
			is_player_falling = true;
		}
	}
}

void Player::DrawPlayer(bool loadedInitial, Shader ourShader)
{
	if (!loadedInitial)
	{
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
															  // Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width, height;
		unsigned char* image = SOIL_load_image("images/player/test-player.png", &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.	


		glGenVertexArrays(1, &VAO_p);
		glGenBuffers(1, &VBO_p);
		glBindVertexArray(VAO_p);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_p);
		glBufferData(GL_ARRAY_BUFFER, sizeof(player_vertices), player_vertices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0); // Unbind VAO

		glGenVertexArrays(1, &VAO_p_hitbox);
		glGenBuffers(1, &VBO_p_hitbox);
		glBindVertexArray(VAO_p_hitbox);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_p_hitbox);
		glBufferData(GL_ARRAY_BUFFER, sizeof(player_hitbox_vertices), player_hitbox_vertices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0); // Unbind VAO	

	}

	glm::mat4 model;
	glm::vec3 tempPos;
	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
	model = glm::translate(model, player_position);

	glLineWidth(3.0f);
	glBindVertexArray(VAO_p_hitbox);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_LINES, 0, 8);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(VAO_p);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
}