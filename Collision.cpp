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
GLfloat return_values[3]; //temp_m, temp_c
GLfloat player_on_slope_details[6] = { 0, 0, 0, 0, 0, 0 }; //x1, x2, y1, y2, m, c

GLfloat * Collision::DetectWall(GLfloat player_hitbox_vertices[], glm::vec3 player_position, GLfloat player_movement[2], GLint player_direction, GLfloat player_movement_speed) //player_movement - x movement, y movement ; player_direction 0,1,2,3 / L,R,U,D
{
	bool has_intersected = false;
	GLint player_vertices_to_check[2];

	if (player_direction == 0)
	{
		player_vertices_to_check[0] = 0; //42 55 14 27
		player_vertices_to_check[1] = 4;
	}
	if (player_direction == 1)
	{
		player_vertices_to_check[0] = 0;
		player_vertices_to_check[1] = 4;
	}

	player_position[0] += player_movement_speed;

	for (int k = 0; k < 2; k++)
	{
		GLfloat origin_distance = sqrt(pow(object_position[k][1] - player_position[1] - 0.5f, 2) + pow(object_position[k][0] - player_position[0] - 0.5f, 2));
		if (origin_distance < 0)
			origin_distance *= -1;

		if (origin_distance < 10.5f)
		{
			for (int i = 0; i < number_of_hitbox_lines[k] * 14; i++)
			{
				if ((i + 1) % 7 == 1)
				{
					object_points.push_back(object_hitbox[i] + object_position[k][0]);
				}
				if ((i + 1) % 7 == 2)
				{
					object_points.push_back(object_hitbox[i] + object_position[k][1]);
				}
				if ((i + 1) % 7 == 3)
				{
					object_points.push_back(object_hitbox[i] + object_position[k][2]);
				}
			}


			GLfloat hitbox_x1;
			GLfloat hitbox_y1;
			GLfloat hitbox_x2;
			GLfloat hitbox_y2;

			
			//player_position[1] += 0.001f;

			for (int j = 0; j < number_of_hitbox_lines[k]; j++)
			{

				if (!has_intersected)
				{
					hitbox_x1 = object_points[6 * j];
					hitbox_y1 = object_points[6 * j + 1];
					hitbox_x2 = object_points[6 * j + 3];
					hitbox_y2 = object_points[6 * j + 4];

					//std::cout << "i: " << i << "  hitbox values x1 y1 x2 y2: " << hitbox_x1 << " " << hitbox_y1 << " " << hitbox_x2 << " " << hitbox_y2 << " \n";

					if (hitbox_x2 == hitbox_x1)
					{
						//std::cout << "called 1\n";
						temp_m = 1;
						temp_y = 0;
						temp_c = hitbox_x1;
					}
					else if (hitbox_y1 == hitbox_y2)
					{
						//std::cout << j << " <-- i ; called 2\n";
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
				}


				
				if (!has_intersected)
				{
					for (int i = player_vertices_to_check[0]; i < player_vertices_to_check[1]; i++)
					{
						if (player_points[6 * i] == player_points[6 * i + 3])
						{
							//std::cout << i << " called 1\n" << player_hitbox_vertices[3 * i] << " " << player_hitbox_vertices[3 * i + 3] << "\n\n";
							temp_m_player = 1;
							temp_y_player = 0;
							temp_c_player = player_points[6 * i] + player_position[0];
						}
						else if (player_points[6 * i + 1] == player_points[6 * i + 4])
						{
							//std::cout << i << " called 2\n" << player_hitbox_vertices[3 * i + 1] << " " << player_hitbox_vertices[3 * i + 4] << "\n\n";
							temp_m_player = 0;
							temp_y_player = 1;
							temp_c_player = player_points[6 * i + 1] + player_position[1];
						}
						else
						{
							std::cout << "called 3\n";
							temp_y_player = 1;
							temp_m_player = (player_points[6 * i + 1] + player_points[6 * i + 4]) / (player_points[6 * i] - player_points[6 * i + 3]);
							temp_c_player = ((player_points[6 * i + 1] + player_position[1]) - ((player_points[6 * i] + player_position[0]) *temp_m));
						}

						bool is_gradient_inf = false;
						GLfloat x_intersect;
						x_intersect = (temp_c_player - temp_c) / (temp_m - temp_m_player ); //issues here - should output the accurate result as temp_m_player - temp_m? but proving otherwise
						GLfloat y_intersect = temp_m_player * x_intersect + temp_c_player;

						//std::cout << " k: " << k << "   i: " << i << " x, y: " << x_intersect << " " << y_intersect << "\n";
						
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

						GLfloat player_h_x1 = 0, player_h_x2 = 0, player_h_y1 = 0, player_h_y2 = 0;

						if (player_points[6 * i] > player_points[6 * i + 3])
						{
							player_h_x1 = player_points[6 * i] + player_position[0];
							player_h_x2 = player_points[6 * i + 3] + player_position[0];
						}
						else
						{
							player_h_x1 = player_points[6 * i + 3] + player_position[0];
							player_h_x2 = player_points[6 * i] + player_position[0];
						}

						if (player_points[6 * i + 1] > player_points[6 * i + 4])
						{
							player_h_y1 = player_points[6 * i + 1] + player_position[1];
							player_h_y2 = player_points[6 * i + 4] + player_position[1];
						}
						else
						{
							player_h_y1 = player_points[6 * i + 4] + player_position[1];
							player_h_y2 = player_points[6 * i + 1] + player_position[1];
						}


						//std::cout << temp_c_player << " " << temp_c << " " << temp_m << " " << temp_m_player << "\n";
						//std::cout << i << " : " << x_intersect << " " << y_intersect << " : " << hitbox_x1 << " " << hitbox_y1 << " : " << hitbox_x2 << " " << hitbox_y2 << " : " << player_h_x1 << " " << player_h_y1 << " : " << player_h_x2  << " " << player_h_y2 << "\n";

						/*player_h_x1 = player_hitbox_vertices[3 * i] + player_position[0];
						player_h_x2 = player_hitbox_vertices[3 * i + 3] + player_position[0];
						player_h_y1 = player_hitbox_vertices[3 * i + 1] + player_position[1];
						player_h_y2 = player_hitbox_vertices[3 * i + 4] + player_position[1];*/

						/*if (!is_gradient_inf)
						{
							//std::cout << "deets: " << x_intersect << ", " << y_intersect << " : " << hitbox_x1 << ", " << hitbox_x2 << ", " << hitbox_y1 << ", " << hitbox_y2 << " : " << player_h_x1 << ", " << player_h_x1 << ", " << player_h_x1 << ", " << player_h_x1 << "\n\n";
							if (j == 1)
							{
								std::cout << i << "  deets: " << x_intersect << ", " << y_intersect << " : " << hitbox_x1 << ", " << hitbox_x2 << ", " << hitbox_y1 << ", " << hitbox_y2 << " : " << player_h_x1 << ", " << player_h_x2 << ", " << player_h_y1 << ", " << player_h_y2 << "\n";
								std::cout << "temp m: " << temp_m << " " << temp_m_player << " temp c: " << temp_c << " " << temp_c_player << "     " << temp_y_player << "\n";
								if ((x_intersect >= hitbox_x2 && x_intersect <= hitbox_x1 && y_intersect >= hitbox_y2 && y_intersect <= hitbox_y1))
									std::cout << "first half true :";
								if ((x_intersect >= player_h_x2 && x_intersect <= player_h_x1 && y_intersect >= player_h_y2 && y_intersect <= player_h_y1))
									std::cout << "second half true ";

								std::cout << "\n\n";
							}

							//std::cout << player_h_y1 << " " << hitbox_y1 << " " << player_h_y2 << " " << hitbox_y2 << "\n";
							if (temp_m == 0 && false)
							{
								if (((hitbox_y1 - 0.03f < player_h_y1 || hitbox_y1 - 0.03f < player_h_y2) && (hitbox_y1 + 0.03f > player_h_y1 || hitbox_y1 + 0.03f > player_h_y2) &&
									((player_h_x2 < hitbox_x1 && player_h_x2 > hitbox_x2) || (player_h_x1 < hitbox_x1 && player_h_x1 > hitbox_x2))))
								{
									std::cout << " A collision\n";
									//std::cout << temp_m << " " << temp_m_player << "\n";
									return 0;
								}
							}
							else if ((x_intersect >= hitbox_x2 && x_intersect <= hitbox_x1 && y_intersect >= hitbox_y2 && y_intersect <= hitbox_y1) && (x_intersect >= player_h_x2 && x_intersect <= player_h_x1 && y_intersect >= player_h_y2 && y_intersect <= player_h_y1))
								//if(x_intersect <= player_h_x1 && x_intersect >= player_h_x2 && y_intersect <= player_h_y1 && y_intersect >= player_h_y2 &&
								//	x_intersect <= hitbox_x1 && x_intersect >= hitbox_x2 && y_intersect <= hitbox_y1 && y_intersect >= hitbox_y2)
							{
								//std::cout << i << " : " << x_intersect << " " << y_intersect << " : " << hitbox_x1 << " " << hitbox_y1 << " : " << hitbox_x2 << " " << hitbox_y2 << " : " << player_h_x1 << " " << player_h_y1 << " : " << player_h_x2 << " " << player_h_y2 << "\n\n";
								if (temp_m > 1.0f)
									std::cout << "one\n";
								else if (temp_m < -1.0f)
									std::cout << "two\n";
								std::cout << " B collision\n";
								
								GLfloat return_values[3];
								return_values[0] = 0; //can move
								return_values[1] = temp_m;
								return_values[2] = temp_c;

								if (temp_m < 0)
									temp_m *= -1;

								if (temp_m <= 1.0f)
									return_values[0] = 1;

								return return_values;
							}
						}*/
						if(i == 1)
							std::cout << i << " : " << j << " : " << x_intersect << " " << y_intersect << " : " << hitbox_x1 << " " << hitbox_y1 << " : " << hitbox_x2 << " " << hitbox_y2 << " : " << player_h_x1 << " " << player_h_y1 << " : " << player_h_x2 << " " << player_h_y2 << "\n\n";

						if (is_gradient_inf)
						{
							//std::cout << player_h_x1 << " " << hitbox_x1 << player_h_x2 << " " << hitbox_x2 << "\n";
							if (((hitbox_x1 - 0.02f < player_h_x1 || hitbox_x1 - 0.02f < player_h_x2) && (hitbox_x1 + 0.02f > player_h_x1 || hitbox_x1 + 0.02f > player_h_x2) &&
								((player_h_y2 < hitbox_y1 && player_h_y2 > hitbox_y2) || (player_h_y1 < hitbox_y1 && player_h_y1 > hitbox_y2))))
							{
								std::cout << " C collision\n";
								return_values[0] = 0; //can move

								return return_values;
							}
						}
						else if ((x_intersect >= hitbox_x2 && x_intersect <= hitbox_x1 && y_intersect >= hitbox_y2 && y_intersect <= hitbox_y1) && (x_intersect >= player_h_x2 && x_intersect <= player_h_x1 && y_intersect >= player_h_y2 && y_intersect <= player_h_y1))
							//if(x_intersect <= player_h_x1 && x_intersect >= player_h_x2 && y_intersect <= player_h_y1 && y_intersect >= player_h_y2 &&
							//	x_intersect <= hitbox_x1 && x_intersect >= hitbox_x2 && y_intersect <= hitbox_y1 && y_intersect >= hitbox_y2)
						{
							if (player_position[0] > hitbox_x2 && player_position[0] < hitbox_x1)
							{
								if (temp_m > 1.0f)
									std::cout << "one\n";
								else if (temp_m < -1.0f)
									std::cout << "two\n";
								std::cout << " B collision\n";

								return_values[0] = 0; //can move
								return_values[1] = temp_m;
								return_values[2] = temp_c;

								if (temp_m < 0)
									temp_m *= -1;

								if (temp_m <= 1.0f)
									return_values[0] = 1;

								std::cout << "return vaues 0 1 2:    " << return_values[0] << " " << return_values[1] << " " << return_values[2] << " \n";

								return return_values;
							}
						}
					}
				}
			}
			std::cout << "\n\n";
			object_points.clear();
		}
	}
	GLfloat return_values[3] = { 1, 1, 1 };
	return return_values;
}

GLfloat * Collision::LineIntersection(GLfloat hitbox_x1, GLfloat hitbox_y1, GLfloat hitbox_x2, GLfloat hitbox_y2, std::vector<GLfloat> player_hitbox_vertices, glm::vec3 player_position, GLfloat player_speed)
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

	player_position[1] += player_speed;
	
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

		GLfloat player_h_x1 = 0, player_h_x2 = 0, player_h_y1 = 0, player_h_y2 = 0;
		
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
			//std::cout << player_h_y1 << " " << hitbox_y1 << " " << player_h_y2 << " " << hitbox_y2 << "\n";
			if (temp_m == 0)
			{
				if (((hitbox_y1 - 0.05f < player_h_y1 || hitbox_y1 - 0.05f < player_h_y2) && (hitbox_y1 + 0.05f > player_h_y1 || hitbox_y1 + 0.05f > player_h_y2) && 
					((player_h_x2 < hitbox_x1 && player_h_x2 > hitbox_x2) || (player_h_x1 < hitbox_x1 && player_h_x1 > hitbox_x2))))
				{
					player_on_slope_details[0] = hitbox_x1;
					player_on_slope_details[1] = hitbox_x2;
					player_on_slope_details[2] = hitbox_y1;
					player_on_slope_details[3] = hitbox_y2;
					player_on_slope_details[4] = temp_m;
					player_on_slope_details[5] = temp_c;

					return_values[0] = 0.0f;
					return_values[1] = temp_c;
					return_values[2] = 0;

					if (player_h_y1 < player_h_y2)
					{
						if (hitbox_y1 - player_h_y1 < 0)
							return_values[3] = player_h_y1 - hitbox_y1;
						else
							return_values[3] = hitbox_y1 - player_h_y1;
					}
					else
					{
						if (hitbox_y1 - player_h_y2 < 0)
							return_values[3] = player_h_y2 - hitbox_y1;
						else
							return_values[3] = hitbox_y1 - player_h_y2;
					}
					//std::cout << return_values[2] << " collision 1 : player h x1, 2, y1, 2 : " << player_h_x1 << " " << player_h_x2 << " " << player_h_y1 << " " << player_h_y2 << "\n";
					return return_values;
				}
			}
			else if ((x_intersect >= hitbox_x2 && x_intersect <= hitbox_x1 && y_intersect >= hitbox_y2 && y_intersect <= hitbox_y1) && (x_intersect >= player_h_x2 && x_intersect <= player_h_x1 && y_intersect >= player_h_y2 && y_intersect <= player_h_y1))
				//if(x_intersect <= player_h_x1 && x_intersect >= player_h_x2 && y_intersect <= player_h_y1 && y_intersect >= player_h_y2 &&
				//	x_intersect <= hitbox_x1 && x_intersect >= hitbox_x2 && y_intersect <= hitbox_y1 && y_intersect >= hitbox_y2)
			{
				//std::cout << i << " : " << x_intersect << " " << y_intersect << " : " << hitbox_x1 << " " << hitbox_y1 << " : " << hitbox_x2 << " " << hitbox_y2 << " : " << player_h_x1 << " " << player_h_y1 << " : " << player_h_x2 << " " << player_h_y2 << "\n\n";
				if (temp_m > 1.0f)
					std::cout << "one\n";
				else if (temp_m < -1.0f)
					std::cout << "two\n";
				std::cout << " collision 2\n";
				return_values[0] = temp_m;
				return_values[1] = temp_c;
				return_values[2] = 0;
				return_values[3] = 0;

				std::cout << "deets: " << x_intersect << ", " << y_intersect << " : " << hitbox_x1 << ", " << hitbox_x2 << ", " << hitbox_y1 << ", " << hitbox_y2 << " : " << player_h_x1 << ", " << player_h_x2 << ", " << player_h_y1 << ", " << player_h_y2 << "\n";
				std::cout << "temp m: " << temp_m << " " << temp_m_player << " temp c: " << temp_c << " " << temp_c_player << "     " << temp_y_player << "\n\n";

				player_on_slope_details[0] = hitbox_x1;
				player_on_slope_details[1] = hitbox_x2;
				player_on_slope_details[2] = hitbox_y1;
				player_on_slope_details[3] = hitbox_y2;
				player_on_slope_details[4] = temp_m;
				player_on_slope_details[5] = temp_c;


				return return_values;
			}
		}
		else if(is_gradient_inf)
		{
			//std::cout << player_h_x1 << " " << hitbox_x1 << player_h_x2 << " " << hitbox_x2 << "\n";
			if (((hitbox_x1 - 0.02f < player_h_x1 || hitbox_x1 - 0.02f < player_h_x2) && (hitbox_x1 + 0.02f > player_h_x1 || hitbox_x1 + 0.02f > player_h_x2) &&
				((player_h_y2 < hitbox_y1 && player_h_y2 > hitbox_y2) || (player_h_y1 < hitbox_y1 && player_h_y1 > hitbox_y2))))
			{
				std::cout << " collision 3\n";
				player_on_slope_details[0] = hitbox_x1;
				player_on_slope_details[1] = hitbox_x2;
				player_on_slope_details[2] = hitbox_y1;
				player_on_slope_details[3] = hitbox_y2;
				player_on_slope_details[4] = temp_m;
				player_on_slope_details[5] = temp_c;

				return_values[0] = 0;
				return_values[1] = temp_c;
				return_values[2] = 1;
				return_values[3] = 0;
				return return_values;
			}
		}
	}
	return_values[0] = 0;
	return_values[1] = 0;
	return_values[2] = 1;
	return_values[3] = 0;
	return return_values;
}

GLfloat *intersects;
bool has_intersected = false;
GLint reference_modifier;
GLfloat * Collision::DetectCollision(GLfloat player_hitbox_vertices[], glm::vec3 player_position, bool is_player_falling, GLfloat player_speed)
{
	if (is_player_falling)
		has_intersected = false;

	for (int k = 0; k < 2; k++)
	{
		GLfloat origin_distance = sqrt(pow(object_position[k][1] - player_position[1] - 0.5f, 2) + pow(object_position[k][0] - player_position[0] - 0.5f, 2));
		if (origin_distance < 0)
			origin_distance *= -1;

		if (origin_distance < 10.5f)
		{
			//std::cout << "orig dist: " << origin_distance << " " << k << "\n";

			
			if (k != 0)
			{
				reference_modifier = object_hitbox_length[k - 1];
			}
			else
			{
				reference_modifier = 0;
			}

			for (int i = reference_modifier; i < number_of_hitbox_lines[k] * 14 + reference_modifier; i++) //number of hitbox lines needs to sum them all up prior - do in future //< sizeof(object_hitbox) / sizeof(object_hitbox[0]) / number_of_hitbox_lines[0]
			{
				if ((i + 1) % 7 == 1)
				{
					object_points.push_back(object_hitbox[i] + object_position[k][0]);
				}
				if ((i + 1) % 7 == 2)
				{
					object_points.push_back(object_hitbox[i] + object_position[k][1]);
				}
				if ((i + 1) % 7 == 3)
				{
					object_points.push_back(object_hitbox[i] + object_position[k][2]);
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
			for (int i = 0; i < number_of_hitbox_lines[k]; i++)
			{
				if(!has_intersected && is_player_falling)
					intersects = LineIntersection(object_points[6 * i], object_points[6 * i + 1], object_points[6 * i + 3], object_points[6 * i + 4], player_points, player_position, player_speed);				
			
				if (intersects[2] != 1)
				{
					has_intersected = true;
				}
			}
			object_points.clear();
		}
	}

	return intersects;
}