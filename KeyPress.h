
// Other includes
#pragma once

#include <iostream>

#include "Player.h"
#include "Render.h"
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




extern GLfloat fov;
extern GLfloat cameraSpeed;
extern GLfloat deltaTime;


//to delete probs
extern GLint hasInitLocation;

class KeyPress
{
public:
	void KeyCallback(GLFWwindow* window);

private:
	void DoMovement();


};