// Подключение заголовочного файла
#include "Function_OpenGL.h"

// Переменные для хранения координат опорных точек
float x_inter, y_inter, z_inter;
float x_track, y_track, z_track;
float x_turn, y_turn, z_turn;

// Подключение пространства имен
using namespace std;

/***********************************************************************************
 * @brief Функция расчета точек пересечения линии и сферы
 * @param H Начальная высота ЛА
 * @param V Начальная скорость ЛА
 * @param pitch Угол тангажа
 * @param yaw Угол рысканья
 * @param x_sp Координата x центра сферы
 * @param y_sp Координата y центра сферы
 * @param R_sp Радиус сферы
 * @return Координаты точки пересечения луча и сферы
***********************************************************************************/
struct_inter Intersection_sphere(float H, float V, float pitch, float yaw, float x_sp, float y_sp, float R_sp)
{
	// Переменные для хранения значений параметров прямой
	float V_x, V_y, V_z;
	float m, n, p;
	float A, B, C, D;
	bool flag_loot;
	float t_1, t_2;
	float x_t, y_t, z_t;
	float y_1, y_2;

	// Определение проекций вектора скорости на оси координат
	V_x = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	V_y = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	V_z = V * sin(pitch * GLOBAL_PI / 180);

	// Присвоение значений компонентам направляющего вектора прямой
	m = V_x;
	n = V_y;
	p = V_z;

	// Решение квадратного уравнения
	A = pow(m, 2) + pow(n, 2) + pow(p, 2);
	B = -2 * m * x_sp - 2 * n * y_sp + 2 * p * H;
	C = pow(x_sp, 2) + pow(y_sp, 2) + pow(H, 2) - pow(R_sp, 2);
	// Вычисление дискриминанта
	D = pow(B, 2) - 4 * A * C;
	
	// Если дискриминант меньше нуля - нет пересечения прямой и сферы
	if (D < 0)
	{
		return { 0, 0, 0, false };
	}
	// Если есть пересечение прямой и сферы
	else
	{
		// Одна точка пересечения
		if (D == 0)
		{
			t_1 = (-B) / (2 * A);
			flag_loot = true;
		}
		// Две точки пересечения
		else
		{
			t_1 = (-B + sqrt(D)) / (2 * A);
			t_2 = (-B - sqrt(D)) / (2 * A);
			flag_loot = false;
		}
		// Присваение одной точки
		if (flag_loot == true)
		{
			x_t = m * t_1;
			y_t = n * t_1;
			z_t = p * t_1 + H;
		}
		// Если две точки, то выбираем наиболее ближнюю к началу системы координат
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
		// Возвращаем точку пересечения прямой и сферы
		return { x_t, -y_t, z_t, true };
	}
}

/***********************************************************************************
 * @brief Функция расчета точки конца траектории ЛА в случае, когда нет пересечения со сферой
 * @param H Начальная высота ЛА
 * @param V Начальная скорость ЛА
 * @param pitch Угол тангажа
 * @param yaw Угол рысканья
 * @return Координаты конечной точки траектории ЛА
***********************************************************************************/
struct_inter Not_intersection(float pitch, float yaw, float H, float V)
{
	// Объявление переменных - направляющих векторов прямой
	float a_x, a_y, a_z;
	// Объявление переменных - координат итоговых точек
	float x_t, y_t, z_t;
	// Расчитанные значения
	float t, m, n, p;
	// Диствнции между точками
	float distance_1, distance_2;
	// Вектор длины
	float vector_long = V / 20 * 100;
	
	// Расчет направляющих косинусов прямой с определенным расстоянием
	a_x = vector_long * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	a_y = -vector_long * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	a_z = H + vector_long * sin(pitch * GLOBAL_PI / 180);

	// Расчет направляющих косинусов исходной прямой
	m = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	n = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	p = V * sin(pitch * GLOBAL_PI / 180);

	// Если прямая параллельна исходной плоскости
	if (p == 0)
	{
		return { a_x, a_y, a_z, false };
	}

	// Расчитываем параметр для уравнения
	t = -H / p;
	// Находим координаты точки
	x_t = m * t;
	y_t = - n * t;
	z_t = p * t + H;

	// Расчет расстояния между векторами
	distance_1 = Disrance_two_vectors(0, 0, H, a_x, a_y, a_z);
	distance_2 = Disrance_two_vectors(0, 0, H, x_t, y_t, z_t);

	// Выбор оптимального расстояния
	if (distance_1 < distance_2)
	{
		return { a_x, a_y, a_z, false };
	}
	else
	{
		return { x_t, y_t, z_t, false };
	}
}
/***********************************************************************************
 * @brief Функция расчета начала увода ЛА
 * @param turn_x Координата x - центра окружности ухода ЛА
 * @param turn_y Координата y - центра окружности ухода ЛА
 * @param turn_z Координата z - центра окружности ухода ЛА
 * @param H Начальная высота ЛА
 * @param V Начальная скорость ЛА
 * @param pitch Угол тангажа
 * @param yaw Угол рысканья
 * @return Координаты точки начала ухода ЛА
***********************************************************************************/
struct_track Track_aircraft(float turn_x, float turn_y, float turn_z, float H, float V, float pitch, float yaw)
{
	// Объявление переменных - координат итоговых точек
	float x_1, y_1, z_1;
	// Объявление переменных - направляющих векторов прямой
	float m_track, n_track, p_track;
	// Вычисленный параметр
	float t_turn;

	// Расчет направляющих косинусов прямой
	m_track = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	n_track = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	p_track = V * sin(pitch * GLOBAL_PI / 180);

	// Расчет параметра по формуле нахождения точки, через которую проходит перпендикуляр
	t_turn = -(turn_x * m_track + turn_y * n_track + turn_z * p_track - p_track * H) / (pow(m_track,2) + pow(n_track, 2) + pow(p_track, 2));
	// Находим координаты точки
	x_1 = m_track * t_turn;
	y_1 = -n_track * t_turn;
	z_1 = p_track * t_turn + H;

	return { x_1, y_1, z_1 };
}
/***********************************************************************************
 * @brief Функция расчета точки касания траектории ЛА
 * @param turn_x Координата x - центра окружности ухода ЛА
 * @param turn_y Координата y - центра окружности ухода ЛА
 * @param turn_z Координата z - центра окружности ухода ЛА
 * @param H Начальная высота ЛА
 * @param V Начальная скорость ЛА
 * @param pitch Угол тангажа
 * @param yaw Угол рысканья
 * @param R_turn Радиус окружности увода ЛА
 * @return Координаты касания траектории ЛА
***********************************************************************************/
struct_inter Contact_aircraft(float turn_x, float turn_y, float turn_z, float H, float V, float pitch, float yaw, float R_turn)
{
	// Объявление переменных - координат итоговых точек
	float x_1, y_1, z_1;
	// Объявление переменных - направляющих векторов прямой
	float m_contact, n_contact, p_contact;
	// Вычисленный параметр
	float t_contact;

	// Расчет направляющих косинусов прямой
	m_contact = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	n_contact = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	p_contact = V * sin(pitch * GLOBAL_PI / 180);

	// Расчет параметра прямой
	t_contact = Disrance_two_vectors(0, 0, H + R_turn / sin((90 - pitch) * GLOBAL_PI / 180), turn_x, turn_y, turn_z);
	// Находим координаты точки
	x_1 = m_contact * (t_contact + R_turn);
	y_1 = -n_contact * (t_contact + R_turn);
	z_1 = p_contact * (t_contact + R_turn) + H + R_turn / sin((90 - pitch) * GLOBAL_PI / 180);

	return { x_1, y_1, z_1 };
}

/***********************************************************************************
 * @brief Функция находит радиус ухода ЛА
 * @param H Начальная высота ЛА
 * @param V Начальная скорость ЛА
 * @param pitch Угол тангажа
 * @param yaw Угол рысканья
 * @return Радиус окружности виража
***********************************************************************************/
float Search_R_turn(float H, float V, float pitch, float yaw)
{
	// Угол крена
	float cos_roll;
	// Величина продольной перегрузки
	float n_y;
	// Радиус ухода
	float R_turn;
	// Расчет угла крена
	cos_roll = atanf(tanf(yaw * GLOBAL_PI / 180) / cosf(pitch * GLOBAL_PI / 180));
	// Косинус угла крена
	cos_roll = cosf(cos_roll);

	cout << "Косинус угла крена = " << cos_roll << ";" << endl;
	// Проверка, возможен ли вираж
	if ((cos_roll == 1) || (cos_roll == 0) || (cos_roll == -1))
	{
		R_turn = 0;
		cout << "ВИРАЖ НЕВОЗМОЖЕН!!! НЕДОПУСТИМЫЙ УГОЛ КРЕНА!!!" << endl;
	}
	else
	{
		// Расчет продольной перегрузки
		n_y = 1 / cos_roll;
		// Нахождение радиуса виража
		R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));
		cout << "Радиус виража = " << R_turn << " километров;" << endl;
	}

	return R_turn;
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

	return acos(cos_angle) * 180 / GLOBAL_PI;
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
	distance = sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2) + pow((z_1 - z_2), 2));

	return distance;
}
/***********************************************************************************
 * @brief Функция проверяет, не выходит ли полусфера за границы разрешенной области
 * @param x_1, y_1, z_1 - координаты первой точки
 * @return Если можно изменять состояние полусферы, возвращает true, иначе - false
***********************************************************************************/
bool Check_input_data(float x_r, float y_r, float R)
{
	// Объявление переменной - расстояние до прямой
	float distance;
	// Коэффициенты прямой
	float A = 0;
	float B = 0;
	float C = 0;

	//1 случай - прямая x = 0
	// Установка коэффициентов прямой
	A = 1;
	// Расчет расстояния
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	// Проверка с радиусом полусферы
	if (distance < R)
	{
		return false;
	}

	// 2 случай - прямая  y = 0
	// Аналогично 1 случаю
	A = 0;
	B = 1;
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	if (distance < R)
	{
		return false;
	}
	// 3 случай - прямая  x = 11
	// Аналогично 1 случаю
	A = 1;
	B = 0;
	C = -11;
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	if (distance < R)
	{
		return false;
	}
	// 4 случай - прямая  y = 11
	// Аналогично 1 случаю
	A = 0;
	B = 1;
	C = -11;
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	if (distance < R)
	{
		return false;
	}
	// Если все проверки пройдены, возвращаем true
	return true;
}