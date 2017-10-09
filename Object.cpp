#include "Object.h"

std::vector<GLfloat> object_data_points;
std::vector<GLfloat> object_hitbox;
std::vector<int> start_draw;
std::vector<int> end_draw;
std::vector<glm::vec3> object_position;
std::vector<std::string> texture_name;
std::vector<GLfloat> object_scale;
std::vector<int> number_of_hitbox_lines;

std::vector<int> object_hitbox_length;

GLint number_of_previous_objects = 0;

Object::Object()
{
}


Object::~Object()
{
}

void Object::DetectObjectMouseCollision(GLfloat mouse_x, GLfloat mouse_y)
{

}

void Object::FetchObjectFileData(char* object_names)
{
	std::string line;
	std::ifstream myfile(object_names);

	GLint object_hitbox_count = 0;

	if (myfile.is_open())
	{
		char c;
		std::string temp = "";
		glm::vec3 temp_position = glm::vec3(0.0f, 0.0f, 0.0f);
		int read_number = 0;
		int position_number = 0;

		while (myfile.get(c))
		{
			if (c != ';')
			{
				if (read_number == 0)
				{
					if (c == ',')
					{
						object_data_points.push_back(std::stof(temp));
						temp = "";
					}
					else
					{
						temp.push_back(c);
					}
				}
				else if (read_number == 1)
				{
					if (c == ',')
					{
						object_hitbox.push_back(std::stof(temp));
						object_hitbox_count++;
						temp = "";
					}
					else
					{
						temp.push_back(c);
					}
				}
				else if (read_number == 4)
				{
					if (c == ',')
					{
						temp_position[position_number]= std::stof(temp);
						temp = "";
						position_number++;
					}
					else
					{
						temp.push_back(c);
					}
				}
				else
				{
					temp.push_back(c);
				}
			}
			else
			{
				if (read_number == 0)
				{
					object_data_points.push_back(std::stof(temp));
				}

				if (read_number == 1)
				{
					if(object_hitbox.size() > 0)
						object_hitbox.push_back(std::stof(temp));
					object_hitbox_count++;
				}

				if (read_number == 2)
				{
					start_draw.push_back(stoi(temp));					
				}

				if (read_number == 3)
				{
					end_draw.push_back(stoi(temp));					
				}

				if (read_number == 4)
				{
					temp_position[2] = std::stof(temp);
					object_position.push_back(temp_position);
				}

				if (read_number == 5)
				{
					texture_name.push_back(temp);
				}

				if (read_number == 6)
				{
					object_scale.push_back(stof(temp));
				}

				if (read_number == 7)
				{
					number_of_hitbox_lines.push_back(stoi(temp));
				}

				read_number++;
				temp = "";
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	for (int i = 0; i < number_of_previous_objects; i++)
	{
		object_hitbox_count += object_hitbox_length[i];
	}
	object_hitbox_length.push_back(object_hitbox_count);
	number_of_previous_objects++;
}
