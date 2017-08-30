#include "KeyPress.h"
#include "Render.h"
bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();
void do_rotation(int keyV);
GLfloat rotateSpeed = 0.0f;
bool keyADRelease = true;

void KeyPress::keyCallback(GLFWwindow* window)
{
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();
	do_movement();
	if ((rotateSpeed <= -0.01f || rotateSpeed >= 0.01f) && keyADRelease)
	{
		do_rotation(2);
		//std::cout << "called" << "\n";
	}
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
}



void do_rotation(int keyV) //0-D, 1-S, 2-release
{
	if (keyV == 0)
	{
		if (rotateSpeed >= -0.5f)
		{
			rotateSpeed -= 0.2f * deltaTime;
		}
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (rotatePlaneAngle < 0)
			rotatePlaneAngle = 6.28;

		rotatePlaneAngle += rotateSpeed * deltaTime;
		//std::cout << rotatePlaneAngle; std::cout << "\n";
	}
	else if (keyV == 1)
	{
		if (rotateSpeed <= 0.5f)
		{
			rotateSpeed += 0.2f * deltaTime;
		}
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (rotatePlaneAngle > 6.28)
			rotatePlaneAngle = 0;

		rotatePlaneAngle += rotateSpeed *deltaTime;
		//std::cout << rotatePlaneAngle; std::cout<< "\n";
	}
	else if (keyV == 2)
	{
		if (rotateSpeed < -0.01)
		{
			rotateSpeed += 0.2f * deltaTime;

			if (rotatePlaneAngle > 6.28)
				rotatePlaneAngle = 0;

			rotatePlaneAngle += rotateSpeed *deltaTime;
		}
		else if (rotateSpeed > 0.01)
		{
			rotateSpeed -= 0.2f * deltaTime;

			if (rotatePlaneAngle < 0)
				rotatePlaneAngle = 6.28;

			rotatePlaneAngle += rotateSpeed *deltaTime;
		}
		else
		{
			rotateSpeed = 0;
		}
	}

	//std::cout << rotateSpeed << "\n";
}

bool isSpacePressed;
GLfloat spaceTime;
Render render2;


void KeyPress::space_press()
{
	
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
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
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		std::cout << "A CALLED" << "\n";
		keyADRelease = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		std::cout << "D CALLED" << "\n";
		keyADRelease = true;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		isSpacePressed = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		isSpacePressed = true;
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		//render2.ShootLaser(-1);
	}
}


void do_movement()
{
	// Camera controls
	//std::cout << "testmove";

	if (keys[GLFW_KEY_W])
	{
		//cameraPos += cameraSpeed * cameraUp;
		//for (int i = 0; i == 6; i++)
		//{
		//cameraPos += cameraSpeed * cameraUp;
		if (cameraSpeed <= 5.0f)
		{
			cameraSpeed += deltaTime;
		}


		//cubePositions[1] -= cameraSpeed * cameraUp;
		//	std::cout << "works                       ";
		//}
		//std::cout << "testmove wW";
		//std::cout << deltaTime;
	}
	if (keys[GLFW_KEY_S])
	{
		if (cameraSpeed >= 1.0f)
		{
			cameraSpeed -= deltaTime;
		}

		//cameraPos += cameraSpeed * cameraUp;
		//for (int i = 0; i == 6; i++)
		//{
		//cameraPos += cameraSpeed * cameraUp;
		//cubePositions[0] -= cameraSpeed * cameraUp *glm::mat3(cos(rotatePlaneAngle), -sin(rotatePlaneAngle), 0.3f, sin(rotatePlaneAngle), cos(rotatePlaneAngle), -0.25f, 0, 0, 1) * deltaTime;
		//cubePositions[1] += cameraSpeed * cameraUp;
		//cameraPos -= cameraSpeed * cameraUp * glm::mat3(cos(rotatePlaneAngle), -sin(rotatePlaneAngle), 0.3f, sin(rotatePlaneAngle), cos(rotatePlaneAngle), -0.25f, 0, 0, 1) * deltaTime;
		//cubePositions[1] -= cameraSpeed * cameraUp;
		//	std::cout << "works                       ";
		//}
		//std::cout << "testmove wW";
	}
	if (keys[GLFW_KEY_A])
	{
		keyADRelease = false;
		do_rotation(1);
		/*if (rotateSpeed <= 0.5f)
		{
		rotateSpeed += 0.1f;
		}
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (rotatePlaneAngle > 6.28)
		rotatePlaneAngle = 0;

		rotatePlaneAngle += 5.0f *deltaTime;
		//std::cout << rotatePlaneAngle; std::cout<< "\n";*/

	}
	if (keys[GLFW_KEY_D])
	{
		keyADRelease = false;
		do_rotation(0);
		/*if (rotateSpeed >= -0.5f)
		{
		rotateSpeed -= 0.1f * deltaTime;
		}
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (rotatePlaneAngle < 0)
		rotatePlaneAngle = 6.28;

		rotatePlaneAngle -= 5.0f * deltaTime;
		//std::cout << rotatePlaneAngle; std::cout << "\n";*/

	}

}