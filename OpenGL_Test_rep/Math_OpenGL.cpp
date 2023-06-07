// ����������� ������������� �����
#include "Function_OpenGL.h"

// ���������� ��� �������� ��������� ������� �����
// float x_inter, y_inter, z_inter;
float x_track, y_track, z_track;
float x_turn, y_turn, z_turn;
float x_inter_2 = 0, y_inter_2 = 0, z_inter_2 = 0;
float x_inter_3 = 0, y_inter_3 = 0, z_inter_3 = 0;

// ����������� ������������ ����
using namespace std;

/***********************************************************************************
 * @brief ������� ������� ����� ����������� ����� � �����
 * @param H ��������� ������ ��
 * @param V ��������� �������� ��
 * @param pitch ���� �������
 * @param yaw ���� ��������
 * @param x_sp ���������� x ������ �����
 * @param y_sp ���������� y ������ �����
 * @param R_sp ������ �����
 * @return ���������� ����� ����������� ���� � �����
***********************************************************************************/
struct_inter Intersection_sphere(float H, float V, float pitch, float yaw, float x_sp, float y_sp, float R_sp)
{
	// ���������� ��� �������� �������� ���������� ������
	float V_x, V_y, V_z;
	float m, n, p;
	float A, B, C, D;
	bool flag_loot;
	float t_1, t_2;
	float x_t, y_t, z_t;
	float y_1, y_2;
	// ����������� �������� ������� �������� �� ��� ���������
	V_x = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	V_y = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	V_z = V * sin(pitch * GLOBAL_PI / 180);

	// ���������� �������� ����������� ������������� ������� ������
	m = V_x;
	n = V_y;
	p = V_z;

	// ������� ����������� ���������
	A = pow(m, 2) + pow(n, 2) + pow(p, 2);
	B = -2 * m * x_sp - 2 * n * y_sp + 2 * p * H;
	C = pow(x_sp, 2) + pow(y_sp, 2) + pow(H, 2) - pow(R_sp, 2);
	// ���������� �������������
	D = pow(B, 2) - 4 * A * C;

	// ���� ������������ ������ ���� - ��� ����������� ������ � �����
	if (D < 0)
	{
		return { 0, 0, 0, false };
	}
	// ���� ���� ����������� ������ � �����
	else
	{
		// ���� ����� �����������
		if (D == 0)
		{
			t_1 = (-B) / (2 * A);
		}
		// ��� ����� �����������
		else
		{
			t_1 = (-B + sqrt(D)) / (2 * A);
			t_2 = (-B - sqrt(D)) / (2 * A);
			flag_loot = false;
		}
		// ���������� ����� �����
		if (flag_loot == true)
		{
			x_t = m * t_1;
			y_t = n * t_1;
			z_t = p * t_1 + H;
			x_inter_2 = x_t;
			y_inter_2 = -y_t;
			z_inter_2 = z_t;
		}
		// ���� ��� �����, �� �������� �������� ������� � ������ ������� ���������
		else
		{
			y_1 = n * t_1;
			y_2 = n * t_2;

			if (y_1 < y_2)
			{
				x_t = m * t_1;
				y_t = n * t_1;
				z_t = p * t_1 + H;
				x_inter_2 = m * t_2;
				y_inter_2 = -n * t_2;
				z_inter_2 = p * t_2 + H;
			}
			else
			{
				x_t = m * t_2;
				y_t = n * t_2;
				z_t = p * t_2 + H;
				x_inter_2 = m * t_1;
				y_inter_2 = -n * t_1;
				z_inter_2 = p * t_1 + H;
			}
		}
		// ���������� ����� ����������� ������ � �����
		return { x_t, -y_t, z_t, true };
	}
}

/***********************************************************************************
 * @brief ������� ������� ����� ����� ���������� �� � ������, ����� ��� ����������� �� ������
 * @param H ��������� ������ ��
 * @param V ��������� �������� ��
 * @param pitch ���� �������
 * @param yaw ���� ��������
 * @return ���������� �������� ����� ���������� ��
***********************************************************************************/
struct_inter Not_intersection(float pitch, float yaw, float H, float V)
{
	// ���������� ���������� - ������������ �������� ������
	float a_x, a_y, a_z;
	// ���������� ���������� - ��������� �������� �����
	float x_t, y_t, z_t;
	// ����������� ��������
	float t, m, n, p;
	// ��������� ����� �������
	float distance_1, distance_2;
	// ������ �����
	float vector_long = V / 20 * 100;

	// ������ ������������ ��������� ������ � ������������ �����������
	a_x = vector_long * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	a_y = -vector_long * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	a_z = H + vector_long * sin(pitch * GLOBAL_PI / 180);

	// ������ ������������ ��������� �������� ������
	m = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	n = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	p = V * sin(pitch * GLOBAL_PI / 180);

	// ���� ������ ����������� �������� ���������
	if (p == 0)
	{
		return { a_x, a_y, a_z, false };
	}

	// ����������� �������� ��� ���������
	t = -H / p;
	// ������� ���������� �����
	x_t = m * t;
	y_t = -n * t;
	z_t = p * t + H;
	// �������������� ���� ������� ��� ���������
	if (pitch < 0)
	{
		pitch = pitch + ((-(int(pitch) / 360) + 1) * 360);
	}

	pitch = pitch - ((int(pitch) / 360) * 360);

	if (((pitch * GLOBAL_PI / 180) >= 0) && ((pitch * GLOBAL_PI / 180) <= GLOBAL_PI))
	{
		return { a_x, a_y, a_z, false };
	}
	else
	{
		// ������ ���������� ����� ���������
		distance_1 = Disrance_two_vectors(0, 0, H, a_x, a_y, a_z);
		distance_2 = Disrance_two_vectors(0, 0, H, x_t, y_t, z_t);

		// ����� ������������ ����������
		if (distance_2 > distance_1)
		{
			return { a_x, a_y, a_z, false };
		}
		else
		{
			return { x_t, y_t, z_t, false };
		}
	}
}

/***********************************************************************************
 * @brief ������� ������� ������ ����� ��
 * @param turn_x ���������� x - ������ ���������� ����� ��
 * @param turn_y ���������� y - ������ ���������� ����� ��
 * @param turn_z ���������� z - ������ ���������� ����� ��
 * @param H ��������� ������ ��
 * @param V ��������� �������� ��
 * @param pitch ���� �������
 * @param yaw ���� ��������
 * @return ���������� ����� ������ ����� ��
***********************************************************************************/
struct_track Track_aircraft(float turn_x, float turn_y, float turn_z, float H, float V, float pitch, float yaw)
{
	// ���������� ���������� - ��������� �������� �����
	float x_1, y_1, z_1;
	// ���������� ���������� - ������������ �������� ������
	float m_track, n_track, p_track;
	// ����������� ��������
	float t_turn;
	// ����� ������
	float a, b, c;
	// ��������� �����
	turn_y = -turn_y;

	// ������ ������������ ��������� ������
	m_track = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	n_track = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	p_track = V * sin(pitch * GLOBAL_PI / 180);
	// ����� ������
	a = 0;
	b = 0;
	c = H;

	// �������� �� ������� �� ����
	if ((pow(m_track, 2) + pow(n_track, 2) + pow(p_track, 2)) == 0.0)
	{
		return { 0, 0, 0 };
	}
	// ������ ��������� �� ������� ���������� �����, ����� ������� �������� �������������
	t_turn = -(m_track * (a - turn_x) + n_track * (b - turn_y) + p_track * (c - turn_z)) / (pow(m_track, 2) + pow(n_track, 2) + pow(p_track, 2));

	// ������� ���������� �����
	x_1 = m_track * t_turn + a;
	y_1 = -n_track * t_turn + b;
	z_1 = p_track * t_turn + c;

	return { x_1, y_1, z_1 };
}

struct_turn Angle_turn(float x_sp, float y_sp, float r_sp, float pitch, float yaw, float R_turn, float V, float x_inter, float y_inter, float z_inter, float H)
{
	float x_1, y_1, z_1;
	float sum_rad;
	float buf_x, buf_y, buf_z;
	float m_turn, n_turn, p_turn;
	float flag_inter = 0;
	float t;
	float AB, BQ, OK;
	float tetta;
	float ON;
	float R_1;
	float fi;
	float beta;
	float h;
	float buf_r;
	float AQ;
	float r_1, r_2, r_3;
	float cos_fi;
	float angle_1;
	float angle_2;
	float A, B, C, D;
	float x_0_0, y_0_0, z_0_0;
	float x_1_1, y_1_1, z_1_1;
	float x_2_2, y_2_2, z_2_2;
	float x_3_3, y_3_3, z_3_3;
	float x_4_4, y_4_4, z_4_4;
	float x_inter_op, y_inter_op, z_inter_op;
	float angle_sp;

	y_sp = -y_sp;

	// ������ ������������ ��������� ������
	m_turn = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	n_turn = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	p_turn = V * sin(pitch * GLOBAL_PI / 180);

	cout << p_turn << endl;
	if (p_turn == 0)
	{
		return { 0, 0, 0 };
	}
	if (p_turn < 0)
	{
		// ������ ��������� ����� ����������� ������ � ��������� z = 0
		t = -H / p_turn;
		// ������ ��������� ����� A
		x_1 = m_turn * t;
		y_1 = -n_turn * t;
		z_1 = p_turn * t + H;
	}
	else
	{
		// ������ ��������� ����� ����������� ������ � ��������� z = 0
		t = (12 - H) / p_turn;
		// ������ ��������� ����� A
		x_1 = m_turn * t;
		y_1 = -n_turn * t;
		z_1 = p_turn * t + H;
	}

	// ������ ������ ������������ BOQ
	r_1 = Disrance_two_vectors(x_inter, y_inter, z_inter, x_inter_2, y_inter_2, z_inter_2);
	r_2 = Disrance_two_vectors(x_1, y_1, z_1, x_inter_2, y_inter_2, z_inter_2);
	r_3 = Disrance_two_vectors(x_1, y_1, z_1, x_inter, y_inter, z_inter);

	angle_sp = Angle_two_vectors(x_sp, y_sp, 0, 0, -1, 0);
	// ���� ������� ������ � ��������� OXY
	tetta = abs(pitch);

	// ��������, ����� � ����� ����� �����
	flag_inter = powf((x_1 - x_sp), 2) + powf((y_1 - y_sp), 2) + powf((z_1 - 0.0), 2);

	// ���� ����� ������ �����
	if (flag_inter > powf(r_sp, 2))
	{
		OK = (r_2 + (r_1 / 2)) * abs(tanf(tetta * GLOBAL_PI / 180));
	}
	// ���� ������ �����
	else
	{
		OK = ((r_1 / 2) - r_2) * abs(tanf(tetta * GLOBAL_PI / 180));
	}
	yaw = yaw * GLOBAL_PI / 180;

	R_1 = sqrt(powf(OK, 2) + powf((r_1 / 2), 2));

	ON = (OK * (R_1 + R_turn)) / (OK + R_turn);

	fi = acosf(OK / ON) * 180 / GLOBAL_PI;

	//===============================================================================

	x_inter_3 = x_inter;
	y_inter_3 = y_inter;
	z_inter_3 = z_inter + 1;

	A = (y_inter_2 - y_inter) * (z_inter_3 - z_inter) - (z_inter_2 - z_inter) * (y_inter_3 - y_inter);
	B = (z_inter_2 - z_inter) * (x_inter_3 - x_inter) - (x_inter_2 - x_inter) * (z_inter_3 - z_inter);
	C = (x_inter_2 - x_inter) * (y_inter_3 - y_inter) - (y_inter_2 - y_inter) * (x_inter_3 - x_inter);
	D = -(A * x_inter + B * y_inter + C * z_inter);

	h = (abs(A * x_sp + B * y_sp + C * 0 + D)) / (sqrt(powf(A, 2) + powf(B, 2) + powf(C, 2)));

	beta = 90 + tetta - fi;

	angle_1 = (beta - 90) * GLOBAL_PI / 180;
	angle_2 = GLOBAL_PI / 2 - yaw;

	x_0_0 = 0;
	y_0_0 = 0;
	z_0_0 = R_1 + R_turn;

	x_1_1 = x_0_0 * cos(angle_1) + z_0_0 * sin(angle_1);
	y_1_1 = y_0_0;
	z_1_1 = x_0_0 * sin(angle_1) + z_0_0 * cos(angle_1);

	x_2_2 = (x_1_1 * cos(angle_2) - y_1_1 * sin(angle_2));
	y_2_2 = -(x_1_1 * sin(angle_2) + y_1_1 * cos(angle_2));
	z_2_2 = z_1_1;

	if ((angle_sp - yaw / GLOBAL_PI * 180) <= 0)
	{
		x_3_3 = x_2_2 + h * cos(yaw);
		y_3_3 = y_2_2 + h * sin(yaw);
		z_3_3 = z_2_2;
	}
	else
	{
		x_3_3 = x_2_2 - h * cos(yaw);
		y_3_3 = y_2_2 - h * sin(yaw);
		z_3_3 = z_2_2;
	}

	x_4_4 = x_3_3 + x_sp;
	y_4_4 = y_3_3 + y_sp;
	z_4_4 = z_3_3;

	return { x_4_4, y_4_4, z_4_4, true };
}
/***********************************************************************************
 * @brief ������� ������� ����� ������� ���������� ��
 * @param turn_x ���������� x - ������ ���������� ����� ��
 * @param turn_y ���������� y - ������ ���������� ����� ��
 * @param turn_z ���������� z - ������ ���������� ����� ��
 * @param H ��������� ������ ��
 * @param V ��������� �������� ��
 * @param pitch ���� �������
 * @param yaw ���� ��������
 * @param R_turn ������ ���������� ����� ��
 * @return ���������� ������� ���������� ��
***********************************************************************************/
struct_contact Contact_turn(float x_sp, float y_sp, float r_sp, float pitch, float yaw, float R_turn, float V, float x_inter, float y_inter, float z_inter, float H)
{
	float x_1, y_1, z_1;
	float sum_rad;
	float buf_x, buf_y, buf_z;
	float m_turn, n_turn, p_turn;
	float flag_inter = 0;
	float t;
	float AB, BQ, OK;
	float tetta;
	float ON;
	float R_1;
	float fi;
	float beta;
	float h;
	float buf_r;
	float AQ;
	float r_1, r_2, r_3;
	float cos_fi;
	float angle_1;
	float angle_2;
	float A, B, C, D;
	float x_0_0, y_0_0, z_0_0;
	float x_1_1, y_1_1, z_1_1;
	float x_2_2, y_2_2, z_2_2;
	float x_3_3, y_3_3, z_3_3;
	float x_4_4, y_4_4, z_4_4;
	float x_inter_op, y_inter_op, z_inter_op;
	float angle_sp;

	y_sp = -y_sp;

	// ������ ������������ ��������� ������
	m_turn = V * cos(pitch * GLOBAL_PI / 180) * sin(yaw * GLOBAL_PI / 180);
	n_turn = V * cos(pitch * GLOBAL_PI / 180) * cos(yaw * GLOBAL_PI / 180);
	p_turn = V * sin(pitch * GLOBAL_PI / 180);

	if (p_turn == 0)
	{
		return { 0, 0, 0 };
	}
	if (p_turn < 0)
	{
		// ������ ��������� ����� ����������� ������ � ��������� z = 0
		t = -H / p_turn;
		// ������ ��������� ����� A
		x_1 = m_turn * t;
		y_1 = -n_turn * t;
		z_1 = p_turn * t + H;
	}
	else
	{
		// ������ ��������� ����� ����������� ������ � ��������� z = 0
		t = (12 - H) / p_turn;
		// ������ ��������� ����� A
		x_1 = m_turn * t;
		y_1 = -n_turn * t;
		z_1 = p_turn * t + H;
	}

	// ������ ������ ������������ BOQ
	r_1 = Disrance_two_vectors(x_inter, y_inter, z_inter, x_inter_2, y_inter_2, z_inter_2);
	r_2 = Disrance_two_vectors(x_1, y_1, z_1, x_inter_2, y_inter_2, z_inter_2);
	r_3 = Disrance_two_vectors(x_1, y_1, z_1, x_inter, y_inter, z_inter);

	angle_sp = Angle_two_vectors(x_sp, y_sp, 0, 0, -1, 0);
	// ���� ������� ������ � ��������� OXY
	tetta = abs(pitch);

	// ��������, ����� � ����� ����� �����
	flag_inter = powf((x_1 - x_sp), 2) + powf((y_1 - y_sp), 2) + powf((z_1 - 0.0), 2);

	// ���� ����� ������ �����
	if (flag_inter > powf(r_sp, 2))
	{
		OK = (r_2 + (r_1 / 2)) * abs(tanf(tetta * GLOBAL_PI / 180));
	}
	// ���� ������ �����
	else
	{
		OK = ((r_1 / 2) - r_2) * abs(tanf(tetta * GLOBAL_PI / 180));
	}
	yaw = yaw * GLOBAL_PI / 180;

	R_1 = sqrt(powf(OK, 2) + powf((r_1 / 2), 2));

	ON = (OK * (R_1 + R_turn)) / (OK + R_turn);

	fi = acosf(OK / ON) * 180 / GLOBAL_PI;

	//===============================================================================

	x_inter_3 = x_inter;
	y_inter_3 = y_inter;
	z_inter_3 = z_inter + 1;

	A = (y_inter_2 - y_inter) * (z_inter_3 - z_inter) - (z_inter_2 - z_inter) * (y_inter_3 - y_inter);
	B = (z_inter_2 - z_inter) * (x_inter_3 - x_inter) - (x_inter_2 - x_inter) * (z_inter_3 - z_inter);
	C = (x_inter_2 - x_inter) * (y_inter_3 - y_inter) - (y_inter_2 - y_inter) * (x_inter_3 - x_inter);
	D = -(A * x_inter + B * y_inter + C * z_inter);

	h = (abs(A * x_sp + B * y_sp + C * 0 + D)) / (sqrt(powf(A, 2) + powf(B, 2) + powf(C, 2)));

	beta = 90 + tetta - fi;

	angle_1 = (beta - 90) * GLOBAL_PI / 180;
	angle_2 = GLOBAL_PI / 2 - yaw;

	x_0_0 = 0;
	y_0_0 = 0;
	z_0_0 = R_1;

	x_1_1 = x_0_0 * cos(angle_1) + z_0_0 * sin(angle_1);
	y_1_1 = y_0_0;
	z_1_1 = x_0_0 * sin(angle_1) + z_0_0 * cos(angle_1);

	x_2_2 = (x_1_1 * cos(angle_2) - y_1_1 * sin(angle_2));
	y_2_2 = -(x_1_1 * sin(angle_2) + y_1_1 * cos(angle_2));
	z_2_2 = z_1_1;

	if ((angle_sp - yaw / GLOBAL_PI * 180) <= 0)
	{
		x_3_3 = x_2_2 + h * cos(yaw);
		y_3_3 = y_2_2 + h * sin(yaw);
		z_3_3 = z_2_2;
	}
	else
	{
		x_3_3 = x_2_2 - h * cos(yaw);
		y_3_3 = y_2_2 - h * sin(yaw);
		z_3_3 = z_2_2;
	}

	x_4_4 = x_3_3 + x_sp;
	y_4_4 = y_3_3 + y_sp;
	z_4_4 = z_3_3;

	return { x_4_4, y_4_4, z_4_4 };
}

/***********************************************************************************
 * @brief ������� ������� ������ ����� ��
 * @param H ��������� ������ ��
 * @param V ��������� �������� ��
 * @param pitch ���� �������
 * @param yaw ���� ��������
 * @return ������ ���������� ������
***********************************************************************************/
float Search_R_turn(float H, float V, float pitch, float yaw)
{
	// ���� �����
	float cos_roll;
	// �������� ���������� ����������
	float n_y;
	// ������ �����
	float R_turn;
	// ������ ���� �����
	cos_roll = atanf(tanf(yaw * GLOBAL_PI / 180) / cosf(pitch * GLOBAL_PI / 180));
	// ������� ���� �����
	cos_roll = cosf(cos_roll);
	// ��������, �������� �� �����
	if ((cos_roll == 1) || (cos_roll == 0) || (cos_roll == -1))
	{
		R_turn = 0;
	}
	else
	{
		// ������ ���������� ����������
		n_y = 1 / cos_roll;
		// ���������� ������� ������
		R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));
	}
	return R_turn;
}
/***********************************************************************************
 * @brief ������� ������� ���� ����� ����� ���������
 * @param x_1, y_1, z_1 - ���������� ������� �������
 * @param x_2, y_2, z_2 - ���������� ������� �������
 * @return ���� ����� ����� ��������� � ��������
***********************************************************************************/
float Angle_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2)
{
	// �������� ����
	float cos_angle;

	if (((sqrt(pow(x_1, 2) + pow(y_1, 2) + pow(z_1, 2))) * sqrt(pow(x_2, 2) + pow(y_2, 2) + pow(z_2, 2))) == 0)
	{
		return 0;
	}
	// ���������� ���� ����� ����� ���������
	cos_angle = (x_1 * x_2 + y_1 * y_2 + z_1 * z_2) / ((sqrt(pow(x_1, 2) + pow(y_1, 2) + pow(z_1, 2))) * sqrt(pow(x_2, 2) + pow(y_2, 2) + pow(z_2, 2)));

	// ����������� ����
	return acos(cos_angle) * 180 / GLOBAL_PI;
}

/***********************************************************************************
 * @brief ������� ������� ���������� ����� ����� �������
 * @param x_1, y_1, z_1 - ���������� ������ �����
 * @param x_2, y_2, z_2 - ���������� ������ �����
 * @return ���������� ����� ����� �������
***********************************************************************************/
float Disrance_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2)
{
	float distance = 0;

	// ���������� ���������� ����� ����� �������
	distance = sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2) + pow((z_1 - z_2), 2));

	return distance;
}
/***********************************************************************************
 * @brief ������� ���������, �� ������� �� ��������� �� ������� ����������� �������
 * @param x_1, y_1, z_1 - ���������� ������ �����
 * @return ���� ����� �������� ��������� ���������, ���������� true, ����� - false
***********************************************************************************/
bool Check_input_data(float x_r, float y_r, float R)
{
	// ���������� ���������� - ���������� �� ������
	float distance;
	// ������������ ������
	float A = 0;
	float B = 0;
	float C = 0;

	//1 ������ - ������ x = 0
	// ��������� ������������� ������
	A = 1;
	// ������ ����������
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	// �������� � �������� ���������
	if (distance < R)
	{
		return false;
	}

	// 2 ������ - ������  y = 0
	// ���������� 1 ������
	A = 0;
	B = 1;
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	if (distance < R)
	{
		return false;
	}
	// 3 ������ - ������  x = 11
	// ���������� 1 ������
	A = 1;
	B = 0;
	C = -11;
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	if (distance < R)
	{
		return false;
	}
	// 4 ������ - ������  y = 11
	// ���������� 1 ������
	A = 0;
	B = 1;
	C = -11;
	distance = abs((A * x_r + B * y_r + C) / (sqrt(powf(A, 2) + powf(B, 2))));
	if (distance < R)
	{
		return false;
	}
	// ���� ��� �������� ��������, ���������� true
	return true;
}