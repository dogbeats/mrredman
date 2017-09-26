#ifndef RENDER_H_
#define RENDER_H_

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>

// GLM Mathematics
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "MainGame.h"
#include "Object.h"
#include "Player.h"


#include <iostream>
#include <ctime>
#include <cmath>
#include <string>


extern GLfloat fov;
extern GLfloat cameraSpeed;
extern GLfloat deltaTime;
extern GLfloat globalDeltaTime;
extern GLint hasInitLocation;




class Render
{
	public:
		Render();
		~Render();
		void InitialLoad();
		void Window(GLFWwindow* window, Shader ourShader);
		Shader CompileShader();
		void CallTexture(GLint textureNumber, char* fileName);
		void DrawObj(Shader ourShader, GLFWwindow* window);
		void calculateGlobalDelta();
		void FetchCameraPosition(GLfloat &camera_x, GLfloat &camera_y);

};
#endif