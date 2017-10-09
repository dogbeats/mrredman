#include "Player.h"

GLuint VAO_p, VBO_p, VAO_p_hitbox, VBO_p_hitbox, VAO_p_weapon, VBO_p_weapon, VAO_p_bullet, VBO_p_bullet;

GLfloat player_vertices[] = {
	//head
	0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //bottom 
	-0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 1.0f, //bottom
	0.25f, 0.675f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.796875f, //
	-0.25f, 0.675f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 0.796875f, //
	-0.25f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 1.0f, //bottom
	0.25f, 0.675f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.796875f, //

	//torso
	0.25f, 0.675f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.78125f, //b
	-0.25f, 0.675f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 0.78125f, //
	0.25f, 0.4f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.609375f, //to
	-0.25f, 0.4f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 0.609375f, //t
	-0.25f, 0.675f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 0.78125f, //
	0.25f, 0.4f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.609375f, //bo

	//legs
	0.25f, 0.4f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.59375f, //top right
	-0.25f, 0.4f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 0.59375f, // top left?
	0.25f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.34375f, // bottom right
	-0.25f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 0.34375f, // bottom left
	-0.25f, 0.4f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.5f, 0.59375f, // top left
	0.25f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.34375f // bottom right
};

GLfloat gun_vertices[] = {
	//head
	1.0f, 0.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.3125f, //bottom left
	0.0f, 0.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.3125f, //bottom right
	1.0f, -0.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, //top left
	0.0f, -0.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //top right
	0.0f, 0.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.3125f, //bottom right
	1.0f, -0.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f //bottom left
};

GLfloat bullet_vertices[] = {
	//head
	10.2f, 10.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //bottom left
	0.0f, 10.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //bottom right
	10.2f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //top left
	10.2f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //top right
	0.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, //bottom right
	0.0f, 10.2f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f //bottom left
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

glm::vec3 player_position = glm::vec3(19.5f,  8.0f, 0.0f);
glm::vec3 gun_position = glm::vec3(19.5f, 8.0f, 0.0f);

GLuint texture, texture_bullet;
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
GLfloat player_collision_line_data[3] = { 0, 0, 1 }; // 0 = m
bool is_player_falling = true, is_player_moving = false; //to be moved and determined in game - set as true for collision testing purposes
GLint direction = -1;
GLfloat y_acceleration = 0.0f, x_acceleration = 0.1f, time_since_jump_fall = 1.0f;
GLfloat player_movement_speed[2] = { -0.1f, -0.1f };

GLfloat angle = 0.0f;

glm::vec3 Player::GetPlayerPosition()
{
	return player_position;
}

void Player::RotateArms(double mouse_x1, double mouse_y1)
{
	gun_position = player_position;
	GLfloat line_distance_1, line_distance_2, line_distance_3;

	line_distance_1 = gun_position[0] - mouse_x1;
	line_distance_2 = gun_position[1] - mouse_y1;
	line_distance_3 = sqrt(line_distance_1*line_distance_1 + line_distance_2*line_distance_2);

	//std::cout << "line distance 1,3 :: " << line_distance_1 << " " << line_distance_3  << " : " << mouse_x1 << " " << mouse_y1 << " :: " << gun_position[0] << " " << gun_position[1] << "\n";

	GLfloat pi = 3.142;

	angle = atan(line_distance_2 / line_distance_1);
	angle *= -1;

	if (mouse_x1 < gun_position[0])
		angle += pi;

}

GLint count = 0;
void Player::UpdateXVelocity(GLint direction, GLfloat total_delta_time) //0 left, 1 right, 2 acceleration -> 0,
{
	if (player_delta_time > 0.01667f)
	{
		if (direction == 0)
		{
			if (x_acceleration > -1.0f)
				x_acceleration -= 0.1f * player_delta_time;

			//std::cout << " 1 " << x_acceleration << "\n";
		}
		else if (direction == 1)
		{
			if (x_acceleration < 1.0f)
				x_acceleration += 0.1f * player_delta_time;
			count++;
			std::cout << " 2 " << x_acceleration << " " << count << "\n";
		}
		else if (direction == -1)
		{
			x_acceleration = 0; //to become deceleration
		}

		//player_delta_time = 0;
	}

	
}

void Player::PlayerAir(GLfloat total_delta_time)
{
	GLfloat distance_y = 0, distance_tot = 0;

	player_delta_time += total_delta_time;	

	//std::cout << "player pos " << player_position[0] << " " << player_position[1] << "\n";

	if (direction >= 0 && player_delta_time > 0.0167f)
		MovePlayer(direction, total_delta_time);

	if (direction == -1 && x_acceleration != 0)
	{
		UpdateXVelocity(-1, total_delta_time);
	}

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
				/*distance_y = (player_on_ground[0] * (player_position[0] + player_on_ground[0] * player_position[1]) + player_on_ground[1]) / (player_on_ground[0] * player_on_ground[0] + 1);
				GLfloat temp_denom = player_on_ground[0] * player_position[0] + player_position[1] + player_on_ground[1];
				if (temp_denom < 0)
				{
					temp_denom *= -1;
				}
				distance_tot = temp_denom / sqrt(player_on_ground[0] * player_on_ground[0] + 1);*/
				
				//std::cout << "dist y " << distance_y << " " << "y accel " << y_acceleration << "  pp y " << player_position[1] << " temp denom  " << distance_tot << "\n";
				//std::cout << "player pos x y " << player_position[0] << " " << player_position[1] << "\n";
				//std::cout << "pog m c  " << player_on_ground[0] << " " << player_on_ground[1] << " \n";

				GLfloat x_distance = player_on_ground[4] - player_position[0];
				if (x_distance < 0)
					x_distance *= -1;

				std::cout << "\n x dist " << x_distance << " " << player_on_ground[4] << " " << player_position[0] << "\n";

				if (x_distance < 1.0f)
				{
					//player_position[0] = player_on_ground[3];
					std::cout << "\n yes some stuff \n";
				}

				is_player_falling = false;
				player_jump = false;
				
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
		time_since_jump_fall += total_delta_time;

		if (y_acceleration < 0.01f)
		{
			y_acceleration = 0.0f;
			player_jump = false;
			time_since_jump_fall = 1.0f;
			is_player_falling = true;
		}

		player_position[1] += y_acceleration;
	}

	if (!is_player_falling && !player_jump)
	{
		time_since_jump_fall = 1.0f;
		y_acceleration = 0.0f;
	}

	if (player_delta_time > 0.01667f)
	{
		player_delta_time = 0.0f;
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

void Player::StartMovement(GLint key)
{
	is_player_moving = true;
	direction = key;
}

void Player::EndMovement()
{
	direction = -1;
}

GLfloat temporary_line_data[2] = { 0 , 0 };

void Player::UpdatePlayerPosition()
{
	GLfloat dist_to_corner;
	GLfloat * can_move_in_direction;

	can_move_in_direction = 0;
	can_move_in_direction = collision.DetectWall(player_hitbox_vertices, player_position, player_movement_speed, 0, x_acceleration);

	std::cout << " key = 0 " << is_player_falling << " " << player_jump << " " << can_move_in_direction[0] << "\n";


	if (can_move_in_direction[0] == 1)
	{
		std::cout << "pc line data " << player_collision_line_data[0] << " " << player_collision_line_data[1] << " :: " << player_vertices[126] << " " << player_vertices[127] << " \n";

		//player_vertices[109] = 0.4 + player_collision_line_data[0];
		//player_vertices[118] = 0.4 + player_collision_line_data[0];
		player_vertices[127] = 0.0 + 0.25 * player_collision_line_data[0];
		player_vertices[136] = 0.0 - 0.25 * player_collision_line_data[0];
		//player_vertices[145] = 0.4 + player_collision_line_data[0];
		player_vertices[154] = 0.0 + 0.25 * player_collision_line_data[0];

		glBindBuffer(GL_ARRAY_BUFFER, VBO_p);
		glBufferData(GL_ARRAY_BUFFER, sizeof(player_vertices), player_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (is_player_falling || player_jump)
		{
			player_position[0] += x_acceleration;
			//player_position[1] -= 0.1f;
		}
		if ((can_move_in_direction[1] <= 0.0f && can_move_in_direction[1] >= -1.0f) || (can_move_in_direction[1] >= 0.0f && can_move_in_direction[1] <= 1.0f))
		{
			player_collision_line_data[0] = can_move_in_direction[1];
			player_collision_line_data[1] = can_move_in_direction[2];
			player_position[0] += x_acceleration;
			player_position[1] = player_position[0] * player_collision_line_data[0] + player_collision_line_data[1];
		}

		else
		{
			//std::cout << "fdsfd \n\n move: ";
			//std::cout << player_collision_line_data[0] << "  " << player_collision_line_data[1] << "\n\n";
			player_position[0] += x_acceleration;
			//dist_to_corner = 0.70711;
			player_position[1] = player_position[0] * player_collision_line_data[0] + player_collision_line_data[1];
			std::cout << "Find 1";
		}
	}
	else if (can_move_in_direction[0] < 0)
	{
		std::cout << "\nfallingssssssssssssssssssssss\n";
		player_position[0] += x_acceleration;
		is_player_falling = true;
	}
}

void Player::MovePlayer(GLint key, GLfloat total_delta_time)
{


	//std::cout << "player delta ttime :: " << player_delta_time << "\n";

	/*
		0 = MOVE LEFT
		1 = MOVE RIGHT
	*/

	switch (key)
	{
	case 0 :
		UpdateXVelocity(0, total_delta_time);
		UpdatePlayerPosition();
			 break;
	case 1: 
		UpdateXVelocity(1, total_delta_time);
		UpdatePlayerPosition();
			break;
	}
}

std::vector<Projectile> test_bullet;
std::vector<glm::mat4> bullet_model;

void Player::FireBullet()
{
	glm::mat4 mat_temp;
	bullet_model.push_back(mat_temp);
	test_bullet.push_back( Projectile() );
	test_bullet[test_bullet.size()-1].gradient = 1.0f;
	test_bullet[test_bullet.size()-1].position = glm::vec3(10.0f, 2.0f, 0.0f);
	test_bullet[test_bullet.size()-1].FireBullet(player_delta_time, 1, 1.0f);
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
		unsigned char* image = SOIL_load_image("images/player/new-man.png", &width, &height, 0, SOIL_LOAD_RGBA);
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


		glGenVertexArrays(1, &VAO_p_weapon);
		glGenBuffers(1, &VBO_p_weapon);
		glBindVertexArray(VAO_p_weapon);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_p_weapon);
		glBufferData(GL_ARRAY_BUFFER, sizeof(gun_vertices), gun_vertices, GL_STATIC_DRAW);

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


		//Bullet texture - temporary
		glGenTextures(1, &texture_bullet);

		glBindTexture(GL_TEXTURE_2D, texture_bullet); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											   // Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width2, height2;
		unsigned char * image2 = SOIL_load_image("images/bullet.png", &width2, &height2, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image2);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.	


		glGenVertexArrays(1, &VAO_p_bullet);
		glGenBuffers(1, &VBO_p_bullet);
		glBindVertexArray(VAO_p_bullet);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_p_bullet);
		glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_vertices), bullet_vertices, GL_STATIC_DRAW);

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

	}



	glm::mat4 model[2];
	glm::vec3 tempPos;
	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
	model[1] = glm::translate(model[1], player_position);

	glLineWidth(3.0f);
	glBindVertexArray(VAO_p_hitbox);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[1]));
	glDrawArrays(GL_LINES, 0, 8);
	glBindTexture(GL_TEXTURE_2D, 0);

	gun_position += glm::vec3(-0.05f, 0.6f, 0.0f);

	model[0] = glm::translate(model[0], gun_position);
	//model[0] = glm::translate(model[0], glm::vec3(0.5f, 0.5f, 0.0f));
	model[0] = glm::rotate(model[0], angle, glm::vec3(0.0f, 0.0f, 1.0f));

	glBindVertexArray(VAO_p_weapon);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[0]));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);


	glBindVertexArray(VAO_p);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[1]));
	glDrawArrays(GL_TRIANGLES, 0, 18);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (bullet_model.size() > 0)
	{
		for (int i = 0; i < test_bullet.size(); i++)
		{
			test_bullet[i].FireBullet(player_delta_time, 1, 1.0f); //0 = left, 1 = right (bool)
			bullet_model[i] = glm::translate(bullet_model[i], test_bullet[i].position);
			glBindVertexArray(VAO_p_bullet);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_bullet);
			glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(bullet_model[i]));
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindTexture(GL_TEXTURE_2D, 0);

			if (test_bullet[i].is_existing == false)
			{
				test_bullet.erase(test_bullet.begin() + i);
				bullet_model.erase(bullet_model.begin() + i);
			}
		}
	}

	glBindVertexArray(0);
}