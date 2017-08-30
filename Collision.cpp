#include "Collision.h"

std::vector<GLfloat> object_points, player_points; 

/*
a = (2,5), b = (6,1)
y = mx + c

1 = 3m + c
2 = 6m + c

//

y = 5x + 10

*/

/*0.5f, 0.5f, 0.0f,f, 
-0.5f, 0.5f, 0.5f, , 
-0.5f, 0.5f, 0.5f, , 
-0.5f, -0.5f, 0.5f,f, 
-0.5f, -0.5f, 0.5f,f, 
0.0f, -0.5f, 0.0f, , 
0.0f, -0.5f, 0.0f, , 
0.5f, 0.5f, 0.0f, 1*/



Collision::Collision()
{
}


Collision::~Collision()
{
}

GLfloat distance = 0;
GLfloat update_time = 0.0f;


bool Collision::Intersects(GLfloat hitbox_x1, GLfloat hitbox_y1, GLfloat hitbox_x2, GLfloat hitbox_y2, std::vector<GLfloat> player_hitbox_vertices, glm::vec3 player_position)
{
	//std::cout << "pos" << player_hitbox_vertices[1] + player_position[1] << "\n\n";
	for (int i = 0; i < 8; i++)
	{
		GLfloat temp_m, temp_c, temp_y;
		GLfloat numerator;

		if (hitbox_x2 == hitbox_x1)
		{
			std::cout << "called 1\n";
			temp_m = -1;
			temp_y = 0;
			temp_c = -hitbox_x1;
		}
		else if (hitbox_y1 == hitbox_y2)
		{
			std::cout << "called 2\n";
			temp_m = 0;
			temp_y = 1;
			temp_c = -hitbox_y1;
		}
		else
		{
			std::cout << "called 3\n";
			temp_y = 1;
			temp_m = -(hitbox_y2 - hitbox_y1) / (hitbox_x2 - hitbox_x1);
			temp_c = -(hitbox_y2 - -(hitbox_x2*temp_m));
		}


		numerator = (temp_m * (player_hitbox_vertices[i*3] + player_position[0])) + (player_hitbox_vertices[i * 3 + 1] + player_position[1]) * temp_y + temp_c; // (A*M_x + B*M_y + C) A=LINE X VAL, B=LINE Y VAL -> M(x/y) = point x/y
		//if(a & b != 0)
		if (numerator < 0)
		{
			numerator *= -1;
		}

		distance = numerator / sqrt(pow(temp_m, 2) + 1 * temp_y);

		std::cout << numerator << " : " << temp_m << " : " << temp_y << " : " << sqrt(pow(temp_m, 2) + 1 * temp_y) << " : " << hitbox_x1 << " " << hitbox_x2 << " " << hitbox_y1 << " " << hitbox_y2 << " : " << player_hitbox_vertices[i * 3] + player_position[0] << " " << player_hitbox_vertices[i * 3 + 1] + player_position[1] << "\n";
		std::cout << "sqrt" << temp_m << "+" << 1 * temp_y << "\n\n";
		std::cout << i << "\n";
		std::cout << temp_m << "*" << player_hitbox_vertices[i * 3]  << "+" << player_hitbox_vertices[i * 3 + 1]  << "*" << player_position[1] << "+" << temp_c << "\n\n";
		
		if (distance > 0.0f && distance < 0.02f)
		{
			std::cout << distance << "\n";
			return true;
		}
	}

	return false;
}

bool intersects = false;

bool Collision::DetectCollision(GLfloat player_hitbox_vertices[], glm::vec3 player_position)
{
	update_time += 0.01f;

	GLfloat origin_distance = sqrt(pow(object_position[0][1] - player_position[1], 2) + pow(object_position[0][0] - player_position[0], 2));
	if (origin_distance < 0)
		origin_distance *= -1;

	//std::cout << "orig dist: " << origin_distance << "\n";

	if (origin_distance < 31.5f)
	{
		for (int i = 0; i < number_of_hitbox_lines[0] * 14; i++) //number of hitbox lines needs to sum them all up prior - do in future //< sizeof(object_hitbox) / sizeof(object_hitbox[0]) / number_of_hitbox_lines[0]
		{

			if ((i + 1) % 7 == 1)
			{
				object_points.push_back(object_hitbox[i] + object_position[0][0]);
			}
			if ((i + 1) % 7 == 2)
			{
				object_points.push_back(object_hitbox[i] + object_position[0][1]);
			}
			if ((i + 1) % 7 == 3)
			{
				object_points.push_back(object_hitbox[i] + object_position[0][2]);
			}

		}

		for (int i = 0; i < 8 * 7; i++) //number of hitbox lines needs to sum them all up prior - do in future //< sizeof(object_hitbox) / sizeof(object_hitbox[0]) / number_of_hitbox_lines[0]
		{

			if ((i + 1) % 7 == 1)
			{
				player_points.push_back(player_hitbox_vertices[i]);
			}
			if ((i + 1) % 7 == 2)
			{
				player_points.push_back(player_hitbox_vertices[i]);
			}
			if ((i + 1) % 7 == 3)
			{
				player_points.push_back(player_hitbox_vertices[i]);
			}

			//std::cout << (i + 1) % 8 << " ";
		}

		//std::cout << lines[0][0] << " " << lines[0][1] << " " << lines[0][2] << " ";
		for (int i = 0; i < 4; i++)
		{
			if (!intersects)
			{
				//intersects = Intersects(1,3,1,2, player_points, player_position);
				intersects = Intersects(object_points[6 * i], object_points[6 * i + 1], object_points[6 * i + 3], object_points[6 * i + 4], player_points, player_position);

				//0,1,3,4-6,7,9,10-12,13,15,16
			}
		}

		object_points.clear();
		update_time = 0.0f;
	}

	if (intersects)
	{
		//std::cout << " !! \n";
		return true;
	}
	else
		return false;
}