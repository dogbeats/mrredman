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
GLint point_number;
GLfloat temp_distance_to_origin = 0;
GLfloat number_switch = 0;
GLfloat temp_m, temp_c, temp_y, temp_m_player, temp_c_player, temp_y_player;

bool Collision::LineIntersection(GLfloat hitbox_x1, GLfloat hitbox_y1, GLfloat hitbox_x2, GLfloat hitbox_y2, std::vector<GLfloat> player_hitbox_vertices, glm::vec3 player_position)
{
	//for (int i = 0; i < 24; i++)
	//{
		//std::cout << player_hitbox_vertices[i] << " ";
		//if ((i + 1) % 3 == 0)
	//		std::cout << "\n";
	//}
	//std::cout << "\n";
	
	if (hitbox_x2 == hitbox_x1)
	{
		//std::cout << "called 1\n";
		temp_m = 1;
		temp_y = 0;
		temp_c = hitbox_x1;
	}
	else if (hitbox_y1 == hitbox_y2)
	{
	//	std::cout << "called 2\n";
		temp_m = 0;
		temp_y = 1;
		temp_c = hitbox_y1;
	}
	else
	{
		//std::cout << "called 3\n";
		temp_y = 1;
		temp_m = (hitbox_y2 - hitbox_y1) / (hitbox_x2 - hitbox_x1);
		temp_c = (hitbox_y2 - (hitbox_x2*temp_m));
	}

	for (int i = 0; i < 4; i++)
	{
		
		if (player_hitbox_vertices[6 * i] == player_hitbox_vertices[6 * i + 3])
		{
			//std::cout << i << " called 1\n" << player_hitbox_vertices[3 * i] << " " << player_hitbox_vertices[3 * i + 3] << "\n\n";
			temp_m_player = 1;
			temp_y_player = 0;
			temp_c_player = player_hitbox_vertices[6 * i] + player_position[0];
		}
		else if (player_hitbox_vertices[6 * i + 1] == player_hitbox_vertices[6 * i + 4])
		{
			//std::cout << i << " called 2\n" << player_hitbox_vertices[3 * i + 1] << " " << player_hitbox_vertices[3 * i + 4] << "\n\n";
			temp_m_player = 0;
			temp_y_player = 1;
			temp_c_player = player_hitbox_vertices[6 * i + 1] + player_position[1];
		}
		else
		{
			//std::cout << "called 3\n";
			temp_y_player = 1;
			temp_m_player = (player_hitbox_vertices[6 * i + 1] + player_hitbox_vertices[6 * i + 4]) / (player_hitbox_vertices[6 * i] - player_hitbox_vertices[6 * i + 3]);
			temp_c_player = ((player_hitbox_vertices[6 * i + 1] + player_position[1]) - ((player_hitbox_vertices[6 * i] + player_position[0]) *temp_m));
		}

		bool is_gradient_inf = false;
		GLfloat x_intersect;
		x_intersect = (temp_c_player - temp_c) / (temp_m - temp_m_player);
		GLfloat y_intersect = temp_m * x_intersect + temp_c;

		if (temp_m == temp_m_player)
		{
			x_intersect = hitbox_x1;
			y_intersect = 0;
			is_gradient_inf = true;
		}
		
		//std::cout << x_intersect << " " << y_intersect << "\n\n";
		
		if (hitbox_y2 > hitbox_y1)
		{
			number_switch = hitbox_y1;
			hitbox_y1 = hitbox_y2;
			hitbox_y2 = number_switch;
		}

		if (hitbox_x2 > hitbox_x1)
		{
			number_switch = hitbox_x1;
			hitbox_x1 = hitbox_x2;
			hitbox_x2 = number_switch;
		}

		GLfloat player_h_x1, player_h_x2, player_h_y1, player_h_y2;
		
		if (player_hitbox_vertices[6 * i] > player_hitbox_vertices[6 * i + 3])
		{
			player_h_x1 = player_hitbox_vertices[6 * i] + player_position[0];
			player_h_x2 = player_hitbox_vertices[6 * i + 3] + player_position[0];
		}
		else
		{
			player_h_x1 = player_hitbox_vertices[6 * i + 3] + player_position[0];
			player_h_x2 = player_hitbox_vertices[6 * i] + player_position[0];
		}

		if (player_hitbox_vertices[6 * i + 1] > player_hitbox_vertices[6 * i + 4])
		{
			player_h_y1 = player_hitbox_vertices[6 * i + 1] + player_position[1];
			player_h_y2 = player_hitbox_vertices[6 * i + 4] + player_position[1];
		}
		else
		{
			player_h_y1 = player_hitbox_vertices[6 * i + 4] + player_position[1];
			player_h_y2 = player_hitbox_vertices[6 * i + 1] + player_position[1];
		}


		//std::cout << temp_c_player << " " << temp_c << " " << temp_m << " " << temp_m_player << "\n";
		//std::cout << i << " : " << x_intersect << " " << y_intersect << " : " << hitbox_x1 << " " << hitbox_y1 << " : " << hitbox_x2 << " " << hitbox_y2 << " : " << player_h_x1 << " " << player_h_y1 << " : " << player_h_x2  << " " << player_h_y2 << "\n";

		/*player_h_x1 = player_hitbox_vertices[3 * i] + player_position[0];
		player_h_x2 = player_hitbox_vertices[3 * i + 3] + player_position[0];
		player_h_y1 = player_hitbox_vertices[3 * i + 1] + player_position[1];
		player_h_y2 = player_hitbox_vertices[3 * i + 4] + player_position[1];*/

		if (!is_gradient_inf)
		{
			std::cout << player_h_y1 << " " << hitbox_y1 << " " << player_h_y2 << " " << hitbox_y2 << "\n";
			if (temp_m == 0)
			{
				if (((hitbox_y1 - 0.02f < player_h_y1 || hitbox_y1 - 0.02f < player_h_y2) && (hitbox_y1 + 0.02f > player_h_y1 || hitbox_y1 + 0.02f > player_h_y2) && 
					((player_h_x2 < hitbox_x1 && player_h_x2 > hitbox_x2) || (player_h_x1 < hitbox_x1 && player_h_x1 > hitbox_x2))))
				{
					std::cout << " collision\n";
					return true;
				}
			}
			else if ((x_intersect >= hitbox_x2 && x_intersect <= hitbox_x1 && y_intersect >= hitbox_y2 && y_intersect <= hitbox_y1) && (x_intersect >= player_h_x2 && x_intersect <= player_h_x1 && y_intersect >= player_h_y2 && y_intersect <= player_h_y1))
				//if(x_intersect <= player_h_x1 && x_intersect >= player_h_x2 && y_intersect <= player_h_y1 && y_intersect >= player_h_y2 &&
				//	x_intersect <= hitbox_x1 && x_intersect >= hitbox_x2 && y_intersect <= hitbox_y1 && y_intersect >= hitbox_y2)
			{
				//std::cout << i << " : " << x_intersect << " " << y_intersect << " : " << hitbox_x1 << " " << hitbox_y1 << " : " << hitbox_x2 << " " << hitbox_y2 << " : " << player_h_x1 << " " << player_h_y1 << " : " << player_h_x2 << " " << player_h_y2 << "\n\n";
				std::cout << " collision\n";
				return true;
			}
		}
		else if(is_gradient_inf)
		{
			//std::cout << player_h_x1 << " " << hitbox_x1 << player_h_x2 << " " << hitbox_x2 << "\n";
			if (((hitbox_x1 - 0.02f < player_h_x1 || hitbox_x1 - 0.02f < player_h_x2) && (hitbox_x1 + 0.02f > player_h_x1 || hitbox_x1 + 0.02f > player_h_x2) &&
				((player_h_y2 < hitbox_y1 && player_h_y2 > hitbox_y2) || (player_h_y1 < hitbox_y1 && player_h_y1 > hitbox_y2))))
			{
				std::cout << " collision\n";
				return true;
			}
		}
	}

	return false;
}


bool Collision::Intersects(GLfloat hitbox_x1, GLfloat hitbox_y1, GLfloat hitbox_x2, GLfloat hitbox_y2, std::vector<GLfloat> player_hitbox_vertices, glm::vec3 player_position)
{
	//std::cout << "pos" << player_hitbox_vertices[1] + player_position[1] << "\n\n";
	for (int i = 0; i < 4; i++)
	{
		GLfloat distance_to_origin = sqrt(pow(object_position[0][1] - (player_hitbox_vertices[6*i + 1] + player_position[1]), 2) + pow(object_position[0][0] - (player_hitbox_vertices[6*i] + player_position[0]), 2));
		std::cout << "distance to oriign: " << distance_to_origin << " " << i << "\n";
		if (i == 0)
		{
			temp_distance_to_origin = distance_to_origin;
			point_number = 0;
		}
		else if (distance_to_origin < temp_distance_to_origin)
		{
			temp_distance_to_origin = distance_to_origin;
			point_number = i*2;
		}
	}

	//for (int i = 0; i < 8; i++)
	//{
		GLfloat temp_m, temp_c, temp_y;
		GLfloat numerator;
		GLfloat equation_called = 0;


		if (hitbox_x2 == hitbox_x1)
		{
			equation_called = 1;
			std::cout << "called 1\n";
			temp_m = 1;
			temp_y = 0;
			temp_c = hitbox_x1;
		}
		else if (hitbox_y1 == hitbox_y2)
		{
			equation_called = 2;
			std::cout << "called 2\n";
			temp_m = 0;
			temp_y = 1;
			temp_c = hitbox_y1;
		}
		else
		{
			equation_called = 3;
			std::cout << "called 3\n";
			temp_y = 1;
			temp_m = -(hitbox_y2 - hitbox_y1) / (hitbox_x2 - hitbox_x1);
			temp_c = -(hitbox_y2 - -(hitbox_x2*temp_m));
		}

		std::cout << "y = " << temp_m << "x + " << temp_c << "\n";
		numerator = (temp_m * (player_hitbox_vertices[3 * point_number] + player_position[0])) + (player_hitbox_vertices[3 * point_number + 1] + player_position[1]) * temp_y + temp_c; // (A*M_x + B*M_y + C) A=LINE X VAL, B=LINE Y VAL -> M(x/y) = point x/y
		//if(a & b != 0)
		if (numerator < 0)
		{
			numerator *= -1;
		}

		distance = numerator / sqrt(pow(temp_m, 2) + 1 * temp_y);

		std::cout << numerator << " : " << temp_m << " " << temp_c << " : " << temp_y << " : " << sqrt(pow(temp_m, 2) + 1 * temp_y) << " : " << hitbox_x1 << " " << hitbox_x2 << " " << hitbox_y1 << " " << hitbox_y2 << " : " << player_hitbox_vertices[point_number * 3] + player_position[0] << " " << player_hitbox_vertices[point_number * 3 + 1] + player_position[1] << "\n";
		std::cout << "sqrt" << temp_m << "+" << 1 * temp_y << "\n\n";
		//std::cout << i << "\n";
		//std::cout << temp_m << "*" << player_hitbox_vertices[i * 3]  << "+" << player_hitbox_vertices[i * 3 + 1]  << "*" << player_position[1] << "+" << temp_c << "\n\n";
		
		//std::cout << "i: " << i * 2 << " dist: " << distance_to_origin << "\n\n";
		std::cout << "obj pos " << object_position[0][0] << " " << object_position[0][1] << " player pos " << player_hitbox_vertices[3 * point_number] + player_position[0] << " " << player_hitbox_vertices[3 * point_number + 1] + player_position[1] << " " << numerator << " " << sqrt(pow(temp_m, 2) + 1 * temp_y) << "\n";
		std::cout << "Point Number: " << point_number << "\n";
		std::cout << distance << "\n";

		if (hitbox_y2 > hitbox_y1)
		{
			number_switch = hitbox_y1;
			hitbox_y1 = hitbox_y2;
			hitbox_y2 = number_switch;
		}

		if (hitbox_x2 > hitbox_x1)
		{
			number_switch = hitbox_x1;
			hitbox_x1 = hitbox_x2;
			hitbox_x2 = number_switch;
		}

		if (distance > 0.0f && distance < 0.2f)
		{
			if (equation_called == 1)
			{

			}
			else if (equation_called == 2)
			{

			}
			else if (equation_called == 3)
			{

			}
			else if (equation_called != 0)
			{
				std::cout << distance << "\n";			
				return true;
			}
			
		}
	//}

	return false;
}

bool intersects = false;

bool Collision::DetectCollision(GLfloat player_hitbox_vertices[], glm::vec3 player_position)
{
	GLfloat origin_distance = sqrt(pow(object_position[0][1] - player_position[1] - 0.5f, 2) + pow(object_position[0][0] - player_position[0] -0.5f, 2));
	if (origin_distance < 0)
		origin_distance *= -1;
	

	if (origin_distance < 10.5f)
	{
		//std::cout << "orig dist: " << origin_distance << "\n";
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
				//std::cout << player_hitbox_vertices[i];
			}
			if ((i + 1) % 7 == 2)
			{
				player_points.push_back(player_hitbox_vertices[i]);
				//std::cout << player_hitbox_vertices[i];
			}
			if ((i + 1) % 7 == 3)
			{
				player_points.push_back(player_hitbox_vertices[i]);
				//std::cout << player_hitbox_vertices[i] << "\n";
			}

			//std::cout << (i + 1) % 8 << " ";
		}

		//std::cout << lines[0][0] << " " << lines[0][1] << " " << lines[0][2] << " ";
		for (int i = 0; i < 4; i++)
		{
			//std::cout << player_points[6 * i] << " " << player_points[6 * i + 1] << "                  " << i << "\n";
			//std::cout << player_points[6 * i + 3] << " " << player_points[6 * i + 4] << "\n\n";
			if (!intersects)
			{
				//intersects = Intersects(1,3,1,2, player_points, player_position);
				//std::cout << "box i: " << i << "\n";
				//std::cout << object_points[6 * i] << " " << object_points[6 * i + 1] << " " << object_points[6 * i + 3] << " " << object_points[6 * i + 4] << "\n";
				intersects = LineIntersection(object_points[6 * i], object_points[6 * i + 1], object_points[6 * i + 3], object_points[6 * i + 4], player_points, player_position);
				//0,1,3,4-6,7,9,10-12,13,15,16

			}
		}


		object_points.clear();
	}

	if (intersects)
	{
		//std::cout << " !! \n";
		return true;
	}
	else
		return false;
}