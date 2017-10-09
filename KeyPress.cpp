#include "KeyPress.h"

bool keys[1024];

void KeyAssign(GLFWwindow* window, int key, int scancode, int action, int mode);

Player player2;

void KeyPress::KeyCallback(GLFWwindow* window)
{
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();
	DoMovement();

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyAssign);
}



void KeyAssign(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//Change to switch/case system

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{

		//mainGameT.pauseGameT();
		//glfwSetWindowShouldClose(window, GL_TRUE);
		/*if (pauseGameS)
		pauseGameS = false;
		else
		pauseGameS = true;*/
	}
	

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
			keys[key] = false;

	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS && fov <= 11.6)
	{
		fov += 0.2f;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && fov >= 9.9)
	{
		fov -= 0.2f;
	}

	if (keys[GLFW_KEY_A])
	{
		player2.StartMovement(0);
	}

	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		player2.EndMovement();
	}

	if (keys[GLFW_KEY_D])
	{
		player2.StartMovement(1);
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		player2.EndMovement();
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		player2.PlayerJump();
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		//render2.ShootLaser(-1);
	}

	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		std::cout << "fired bullet\n";
		player2.FireBullet();
	}
}


void KeyPress::DoMovement()
{


}