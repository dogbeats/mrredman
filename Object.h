#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Player.h"

extern std::vector<GLfloat> object_data_points;
extern std::vector<GLfloat> object_hitbox;
extern std::vector<int> start_draw;
extern std::vector<int> end_draw;
extern std::vector<glm::vec3> object_position;
extern std::vector<std::string> texture_name;
extern std::vector<GLfloat> object_scale;
extern std::vector<int> number_of_hitbox_lines;

class Object
{
public:
	Object();
	~Object();
	void FetchObjectFileData(char* object_names);
};

