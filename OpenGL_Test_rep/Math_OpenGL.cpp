// OpenGL_Test_rep.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

// Подключение заголовочных файлов
#include "Function_OpenGL.h"

float x_inter, y_inter, z_inter;
float x_track, y_track, z_track;
float x_turn, y_turn, z_turn;

using namespace std;

/***********************************************************************************
 * @brief Функция расчета точек пересечения траектории ЛА и сферы
 * @param H Начальная высота ЛА
 * @param V Начальная скорость ЛА
 * @param pitch Угол тангажа
 * @param yaw Угол рысканья
 * @param x_sp Координата x центра сферы
 * @param y_sp Координата y центра сферы
 * @param R_sp Радиус сферы
***********************************************************************************/
struct_inter Intersection_sphere(float H, float V, float pitch, float yaw, float x_sp, float y_sp, float R_sp)
{
	float V_x, V_y, V_z;
	float m, n, p;
	float A, B, C, D;

	bool flag_loot;
	float t_1, t_2;
	float x_t, y_t, z_t;
	float y_1, y_2;

	V_x = V * cos(pitch * M_PI / 180) * sin(yaw * M_PI / 180);
	V_y = V * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
	V_z = V * sin(pitch * M_PI / 180);

	m = V_x;
	n = V_y;
	p = V_z;

	A = pow(m, 2) + pow(n, 2) + pow(p, 2);
	B = -2 * m * x_sp - 2 * n * y_sp + 2 * p * H;
	C = pow(x_sp, 2) + pow(y_sp, 2) + pow(H, 2) - pow(R_sp, 2);

	D = pow(B, 2) - 4 * A * C;
	//cout << D << endl;
	
	if (D < 0)
	{
		return { 0, 0, 0, false };
	}
	else
	{

		if (D == 0)
		{
			t_1 = (-B) / (2 * A);
			flag_loot = true;
		}
		else
		{
			t_1 = (-B + sqrt(D)) / (2 * A);
			t_2 = (-B - sqrt(D)) / (2 * A);
			flag_loot = false;
		}

		if (flag_loot == true)
		{
			x_t = m * t_1;
			y_t = n * t_1;
			z_t = p * t_1 + H;
		}

		else
		{
			y_1 = n * t_1;
			y_2 = n * t_2;

			if (y_1 < y_2)
			{
				x_t = m * t_1;
				y_t = n * t_1;
				z_t = p * t_1 + H;
			}
			else
			{
				x_t = m * t_2;
				y_t = n * t_2;
				z_t = p * t_2 + H;
			}
		}

		//x_inter = x_t;
		//y_inter = -y_t;
		//z_inter = z_t;

		return { x_t, -y_t, z_t, true };
	}
}

struct_inter Not_intersection(float pitch, float yaw, float H)
{
	/*
	float t;

	float x_1, y_1, z_1; // x = 0

	float x_2, y_2, z_2; // y = 0

	float x_3, y_3, z_3; // z = 0

	float x_4, y_4, z_4; // x = 12

	float x_5, y_5, z_5; // y = -12

	float x_6, y_6, z_6; // z = 12
	
	// Если прямая пересекает плоскость с уравнением x = 6
	t = 6 / m;

	x_1 = m * t;
	y_1 = -n * t;
	z_1 = p * t + H;

	// Если прямая пересекает плоскость с уравнением y = 6
	t = 6 / n;

	x_2 = m * t;
	y_2 = -n * t;
	z_2 = p * t + H;

	// Если прямая пересекает плоскость с уравнением z = 0
	t = -H / p;

	x_3 = m * t;
	y_3 = -n * t;
	z_3 = p * t + H;

	// Если прямая пересекает плоскость с уравнением x = 12
	t = 12 / m;

	x_4 = m * t;
	y_4 = -n * t;
	z_4 = p * t + H;

	// Если прямая пересекает плоскость с уравнением y = 12
	t = 12 / n;

	x_5 = m * t;
	y_5 = -n * t;
	z_5 = p * t + H;

	// Если прямая пересекает плоскость с уравнением z = 12
	t = (12 - H) / p;

	x_6 = m * t;
	y_6 = -n * t;
	z_6 = p * t + H;

	*/

	float a_x, a_y, a_z;

	float vector_long = H;

	a_x = vector_long * cos(pitch * M_PI / 180) * sin(yaw * M_PI / 180);
	a_y = -vector_long * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
	a_z = vector_long * cos(pitch * M_PI / 180);

	return { a_x, a_y, a_z, false };
}

struct_track Track_aircraft(float turn_x, float turn_y, float turn_z, float H, float V, float pitch, float yaw)
{
	float x_1, y_1, z_1;

	float m_track, n_track, p_track;

	float t_turn;

	m_track = V * cos(pitch * M_PI / 180) * sin(yaw * M_PI / 180);
	n_track = V * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
	p_track = V * sin(pitch * M_PI / 180);

	//cout << p_track << endl;

	t_turn = (turn_x * m_track + turn_y * n_track + turn_z * p_track - p_track * H) / (pow(m_track,2) + pow(n_track, 2) + pow(p_track, 2));

	x_1 = m_track * t_turn;
	y_1 = -n_track * t_turn;
	z_1 = p_track * t_turn + H;

	return { x_1, y_1, z_1 };
}