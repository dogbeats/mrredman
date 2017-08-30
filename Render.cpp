#include "Render.h"



GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);*/
//void do_movement();

// Camera
glm::vec3 cameraPos = glm::vec3(0.3f, 0.2f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec4 cameraUp4 = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch = 0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat fov = 11.0f;
//bool keys[1024];
// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
GLfloat rotatePlaneAngle = 3.142f;
GLfloat delayTime = 0.0f;

time_t timet;
Player player;
Object object;
char* file_names[] = { "objects/test_object.txt" };//, "objects/test_object_2.txt" };

Render::Render()
{

}

Render::~Render()
{
}

int loadedInitial = false;

void Render::InitialLoad()
{
}

GLfloat soundDeltaTime = 0.0f;

GLfloat currentFrame = glfwGetTime();
void Render::calculateGlobalDelta()
{
	currentFrame = glfwGetTime();
	// Calculate deltatime of current frame
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	// Swap the screen buffers
	delayTime += currentFrame;
	globalDeltaTime = deltaTime;
	/*soundDeltaTime += deltaTime;
	if (soundDeltaTime >= 2.0f)
	{
		Sound sound;
		sound.DropSound();
		soundDeltaTime = 0.0f;
	}*/
}

bool pauseGameS = false;
void Render::Window(GLFWwindow* window, Shader ourShader)
{
	DrawObj(ourShader, window);

	//time(&timet);
	//std::cout << currentFrame << "\n" << deltaTime << "\n";
	glfwSwapBuffers(window);
}

Shader Render::CompileShader()
{
	// Build and compile our shader program
	Shader shader("Shaders/shader.vs", "Shaders/shader.frag");
	shader.Use();
	// Camera/View transformation
	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	return shader;
}

GLuint VAO, VBO, EBO;
GLuint VAO_hitbox, VBO_hitbox, EBO_hitbox;

GLuint texture[10];
GLuint texture2;
const char* file;
int textureNumber[] = { 0, 1 };

GLfloat cameraSpeed = 0.001f;

bool isInitialThing = false;

Render render;

GLfloat objectWidthTemp, objectHeightTemp;

void Render::CallTexture(GLint textureNumber, char* fileName)
{
	glGenTextures(1, &texture[textureNumber]);

	glBindTexture(GL_TEXTURE_2D, texture[textureNumber]); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
														  // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.	
}

void Render::DrawObj(Shader ourShader, GLFWwindow* window)
{
	
	if (!loadedInitial)
	{
		for(int i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
			object.FetchObjectFileData(file_names[i]);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		////////////////////////////////////////////////////////Models
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, object_data_points.size() * sizeof(object_data_points), &object_data_points.front(), GL_STATIC_DRAW);

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

		////////////////////////////////////////////////////////Hitbox
		glGenVertexArrays(1, &VAO_hitbox);
		glGenBuffers(1, &VBO_hitbox);
		glBindVertexArray(VAO_hitbox);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_hitbox);
		glBufferData(GL_ARRAY_BUFFER, object_hitbox.size() * sizeof(object_hitbox), &object_hitbox.front(), GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);		
		// Color attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0); // Unbind VAO

		char *temp_texture_name = new char[texture_name[0].length() + 1];
		strcpy_s(temp_texture_name, texture_name[0].length() + 1, texture_name[0].c_str());
		CallTexture(0, temp_texture_name);
		player.DrawPlayer(loadedInitial, ourShader);

		loadedInitial = true;
	}


	if (true) //globalDeltaTime >= 0.0001f
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Camera/View transformation
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection;
		projection = glm::perspective(11.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//text.drawText("abbbababaaa abg", ourShader, cameraUp, cameraSpeed, deltaTime, fov, cubePositions[0]);


		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		// Get their uniform location
		modelLoc = glGetUniformLocation(ourShader.Program, "model");
		viewLoc = glGetUniformLocation(ourShader.Program, "view");
		projLoc = glGetUniformLocation(ourShader.Program, "projection");
		// Pass the matrices to the shaderco
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//text.drawText("ababbaabhello", ourShader, cameraUp, cameraSpeed, deltaTime, fov, cubePositions[0]);


		glBindVertexArray(VAO);

		glm::mat4 model;
		glm::vec3 tempPos;
		
		for (int i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
		{
			//background
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

			model = glm::translate(model, object_position[i]); //* glm::mat4(10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f );//* object_scale[i];
			model *= glm::mat4(object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			if (i == 0)
				glDrawArrays(GL_TRIANGLES, start_draw[i], end_draw[i]);
			else
				glDrawArrays(GL_TRIANGLES, end_draw[i - 1], end_draw[i]);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}
		
		glBindVertexArray(VAO_hitbox);
		
		for (int i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
		{
			
			glBindTexture(GL_TEXTURE_2D, 0);
			//glBindTexture(GL_TEXTURE_2D, texture[0]);
			glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

			model = glm::translate(model, object_position[i]); //* glm::mat4(10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f );//* object_scale[i];
			model *= glm::mat4(object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		
			glLineWidth(1.0f);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			//if (i == 0)
				glDrawArrays(GL_LINES, 0, number_of_hitbox_lines[0]*2);
			//else
				//glDrawArrays(GL_LINES, end_draw[i - 1], end_draw[i]);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}

		glBindVertexArray(0);
		player.DrawPlayer(loadedInitial, ourShader);

	}
}
