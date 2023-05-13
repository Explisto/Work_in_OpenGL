// OpenGL_Test_rep.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// Подключение заголовочного файла
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

	//cout << "Discriminant = " <<D << endl;
	
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

struct_inter Not_intersection(float pitch, float yaw, float H, float V)
{

	float a_x, a_y, a_z;

	//cout << "V = " << V << endl;

	float vector_long = V / 20 * 100;

	a_x = vector_long * cos(pitch * M_PI / 180) * sin(yaw * M_PI / 180);
	a_y = -vector_long * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
	a_z = H + vector_long * sin(pitch * M_PI / 180);

	/*
	a_x = vector_long * cos(pitch * M_PI / 180) * sin(yaw * M_PI / 180);
	a_y = -vector_long * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
	a_z = vector_long * cos(pitch * M_PI / 180);
	*/

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

	t_turn = -(turn_x * m_track + turn_y * n_track + turn_z * p_track - p_track * H) / (pow(m_track,2) + pow(n_track, 2) + pow(p_track, 2));

	x_1 = m_track * t_turn;
	y_1 = -n_track * t_turn;
	z_1 = p_track * t_turn + H;

	return { x_1, y_1, z_1 };
}

/***********************************************************************************
 * @brief Функция находит угол между двумя векторами
 * @param x_1, y_1, z_1 - координаты первого вектора
 * @param x_2, y_2, z_2 - координаты второго вектора
 * @return Угол между двумя векторами в градусах
***********************************************************************************/
float Angle_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2)
{
	float cos_angle;

	// Нахождение угла между двумя векторами
	cos_angle = (x_1 * x_2 + y_1 * y_2 + z_1 * z_2) / ((sqrt(pow(x_1, 2) + pow(y_1, 2) + pow(z_1, 2))) * sqrt(pow(x_2, 2) + pow(y_2, 2) + pow(z_2, 2)));

	return acos(cos_angle) * 180 / M_PI;
}

/***********************************************************************************
 * @brief Функция находит расстояние между двумя точками
 * @param x_1, y_1, z_1 - координаты первой точки
 * @param x_2, y_2, z_2 - координаты второй точки
 * @return Расстояние между двумя точками
***********************************************************************************/
float Disrance_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2)
{
	float distance = 0;

	// Нахождение расстояния между двумя точками
	while (distance < 15)
	{
		distance = sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2) + pow((z_1 - z_2), 2));
		x_2 += 0.5;
		y_2 += 0.5;
		z_2 += 0.5;
	}

	return distance;
}