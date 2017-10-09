#include "MainGame.h"
#include <stdio.h>
#include <irrKlang.h>
bool pauseGame = false;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
double mouse_x_position, mouse_y_position;
GLfloat camera_x, camera_y;
clock_t testa;
GLint secs = 0;
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;
MainGame::MainGame()
{

}

MainGame::~MainGame()
{

}

GLfloat globalDeltaTime;
GLfloat seconds;

// The MAIN function, from here we start the application and run the game loop
int MainGame::run()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Mr Redman", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	glewInit();
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(0);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
	Render render;

	Shader globalShader = render.CompileShader();
	Shader screenShader = render.ScreenShader();
	render.InitialLoad();
	//KeyPress keyPress;


	float total_delta_time = 0;

	KeyPress keyPress;
	Player player;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		testa = clock();
		if (!pauseGame)
		{
			if (total_delta_time > 0.0) //16.67/1000 60fps
			{
				render.Window(window, globalShader, screenShader);
				glfwGetCursorPos(window, &mouse_x_position, &mouse_y_position);
				render.FetchCameraPosition(camera_x, camera_y);

				mouse_x_position = mouse_x_position / WIDTH + camera_x - 0.5;
				mouse_y_position = mouse_y_position / HEIGHT + camera_y - 0.5;
				//std::cout << "mouse x, y " << mouse_x_position << " " << mouse_y_position << "\n";

				player.PlayerAir(total_delta_time);
				player.RotateArms(mouse_x_position, mouse_y_position);

				total_delta_time = 0;
			}

			// Set the required callback functions
			keyPress.KeyCallback(window);

			render.calculateGlobalDelta();
			total_delta_time += globalDeltaTime;
		}
		
		testa = clock() - testa;
		seconds += ((float)testa) / CLOCKS_PER_SEC;
		//printf("%d clicks, %f fps, %f seconds, %f seconds total\n", testa, 1 / (((float)testa) / CLOCKS_PER_SEC), ((float)testa) / CLOCKS_PER_SEC, seconds);

		//printf("%d testa\n", (secs/1000));
		//printf("%f, %f \n", total_delta_time, globalDeltaTime);
	}

	glfwTerminate();
	return 0;
}

void MainGame::pauseGameT()
{
	if (pauseGame == false)
		pauseGame = true;
	else
		pauseGame = false;
}
