#include "Render.h"

// Quad vertices
/*GLfloat quadVertices[] = {
	-10.0f,  10.0f, 1.0f, 1.0f,
	10.0f,  10.0f,  0.0f, 1.0f,
	10.0f, -10.0f,  0.0f, 0.0f,
				
	10.0f, -10.0f,  0.0f, 0.0f,
	-10.0f, -10.0f,  1.0f, 0.0f,
	-10.0f,  10.0f,  1.0f, 1.0f
};*/

GLfloat quadVertices[] = {
	-1.0f,  1.0f,0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, //0,0 = bottom left
	1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
				
	1.0f, -1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f
};

GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);*/
//void do_movement();

// Camera
glm::vec3 cameraPos = glm::vec3(2.5f, 8.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, -1.0f, 0.0f);

//temporary rotation - to delete
GLfloat temp_rotate = 0;

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
char* file_names[] = { "objects/test_object.txt", "objects/test_object_2.txt", "objects/test_object_building.txt" };//, "objects/test_object_2.txt" };

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

GLuint frameBuffer;
GLuint texColorBuffer;
GLuint rboDepthStencil;
void Render::FrameTexture()
{
	// Create framebuffer
	glGenFramebuffers(1, &frameBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// Create texture to hold color buffer
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);


	
	glGenRenderbuffers(1, &rboDepthStencil);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
void Render::Window(GLFWwindow* window, Shader ourShader, Shader screen_shader)
{
	DrawObj(ourShader, screen_shader, window);

	//time(&timet);
	//std::cout << currentFrame << "\n" << deltaTime << "\n";
	glfwSwapBuffers(window);
}

Shader Render::ScreenShader()
{
	Shader screen_shader("Shaders/screen_shader.vs", "Shaders/screen_shader.frag");
	//glm::mat4 view;
	//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return screen_shader;
}

Shader Render::CompileShader()
{
	// Build and compile our shader program
	Shader shader("Shaders/shader.vs", "Shaders/shader.frag");
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

//framebuffer
GLuint vaoQuad;
GLuint vboQuad;


void Render::DrawObj(Shader ourShader, Shader screen_shader, GLFWwindow* window)
{
	if (!loadedInitial)
	{		
		//framebuffer deets
		glGenVertexArrays(1, &vaoQuad);
		glGenBuffers(1, &vboQuad);
		glBindVertexArray(vaoQuad);
		glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

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

		glUniform1i(glGetUniformLocation(screen_shader.Program, "texFramebuffer"), 0);
		FrameTexture();


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

		char *temp_texture_name[3]; //to change to vector

		for (int i = 0; i < 3; i++)
		{
			temp_texture_name[i] = new char[texture_name[i].length() + 1];
			strcpy_s(temp_texture_name[i], texture_name[i].length() + 1, texture_name[i].c_str());
			CallTexture(i, temp_texture_name[i]);
		}
		player.DrawPlayer(loadedInitial, ourShader);

		loadedInitial = true;
	}

	if (true) //globalDeltaTime >= 0.0001f
	{
		glUseProgram(ourShader.Program);
		//cameraPos = glm::vec3(1.0f, 1.0f, 1.0f);
		cameraPos = player.GetPlayerPosition();
		cameraPos[2] = 3.0f;

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

		//temp_rotate = 2.0f;//+= 1.0f * deltaTime;

		//framebuffer
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		


		player.DrawPlayer(loadedInitial, ourShader);
		glBindVertexArray(VAO);

		glm::mat4 model[3], model_hitbox[3];
		glm::vec3 tempPos;
		
		for (int i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
		{
			//background
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

			model[i] = glm::translate(model[i], object_position[i]); //* glm::mat4(10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f );//* object_scale[i];
			model[i] *= glm::mat4(object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

			//if (i == 1)
					//model[i] *= glm::mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos(temp_rotate), -sin(temp_rotate), 0.0f, 0.0f, sin(temp_rotate), cos(temp_rotate), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[i]));
			if (i == 0)
				glDrawArrays(GL_TRIANGLES, start_draw[i], end_draw[i]);
			else
				glDrawArrays(GL_TRIANGLES, end_draw[i - 1], end_draw[i]);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}
		
		glBindVertexArray(VAO_hitbox);
					
		GLint line_count;
		line_count = 0;

		for (int i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
		{
			
			glBindTexture(GL_TEXTURE_2D, 0);
			//glBindTexture(GL_TEXTURE_2D, texture[0]);
			glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
			
			model_hitbox[i] = glm::translate(model_hitbox[i], object_position[i]); //* glm::mat4(10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f );//* object_scale[i];
			model_hitbox[i] *= glm::mat4(object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, object_scale[i], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

			glLineWidth(1.0f);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_hitbox[i]));
			if (i == 0)
				glDrawArrays(GL_LINES, 0, number_of_hitbox_lines[i] * 2);
			else 
				glDrawArrays(GL_LINES, line_count, number_of_hitbox_lines[i] * 2);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			line_count += number_of_hitbox_lines[i] * 2;

		}
		
		//frame buffer
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(vaoQuad);
		glDisable(GL_DEPTH_TEST);
		glUseProgram(screen_shader.Program);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glUniform1i(glGetUniformLocation(screen_shader.Program, "texFramebuffer"), 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glUseProgram(ourShader.Program);
		glBindVertexArray(0);
		
		
	}
}

void Render::FetchCameraPosition(GLfloat &camera_x, GLfloat &camera_y)
{
	camera_x = cameraPos[0];
	camera_y = cameraPos[1];
}
