#pragma once

#include <iostream>
#include <cmath>
#include <ctime>
#include <stdexcept>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>
#include "Render.h"
#include "KeyPress.h"
#include "Shader.h"
#include "Player.h"
#include "Level.h"

// GLM Mathematics
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

//#include "KeyPress.h"


extern GLfloat globalDeltaTime;
extern double mouse_x_position, mouse_y_position;

class MainGame
{
public:
	MainGame();
	~MainGame();
	int run();
	GLFWwindow* window;
	void pauseGameT();

private:

};

