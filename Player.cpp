#include "Player.h"

GLuint VAO_p, VBO_p, VAO_p_hitbox, VBO_p_hitbox;

GLfloat player_vertices[] = {
	1.0f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //bottom left
	0.0f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //bottom right
	1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //top left
	0.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, //top right
	0.0f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //bottom right
	1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //bottom left
};

GLfloat player_hitbox_vertices[] = {
	1.0f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, //0
	0.0f, 1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 1.0f, //2
	0.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, //4
	1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, //6
	1.0f, 1.0f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f
};

glm::vec3 player_position = glm::vec3(0.0f,  4.9f, 0.0f);

GLuint texture;
GLfloat player_delta_time = 0.0f;

//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Player::Player()
{
}


Player::~Player()
{
}

Collision collision;
bool changed_position_after_fall = false;


void Player::PlayerAir(GLfloat total_delta_time)
{
	player_delta_time += total_delta_time;
	
	bool is_player_falling = true; //to be moved and determined in game - set as true for collision testing purposes
	
	if (is_player_falling && player_delta_time > 0.0167f)
	{
		//std::cout << player_position[1] << " " ;
		//GLfloat player_min_max_x_y[] = { 0.0f + player_position[0], 1.0f + player_position[0], 0.0f + player_position[1], 1.0f + player_position[1] };
		//bool player_on_ground = collision.DetectCollision(player_min_max_x_y);
		//std::cout << is_player_falling << std::endl;
		bool player_on_ground = collision.DetectCollision(player_hitbox_vertices, player_position);

		if (player_on_ground == true)
		{
			is_player_falling = false;
		}
		else
		{
			//player_position[0] += 0.05f;
			player_position[1] -= 0.05f;

		}

		player_delta_time = 0.0f;
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