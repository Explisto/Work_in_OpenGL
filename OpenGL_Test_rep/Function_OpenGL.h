#include "Struct_OpenGL.h"

// Подключение библиотек

#include "glew.h" 
#include "glfw3.h"
#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <glut.h>
#include <fstream>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>



#pragma once

// Раздел с описанием глобальных констант
//
// Ускорение свободного падения
float GLOBAL_EARTH_ACSELERATION = 9.8f;
// Число PI
float GLOBAL_PI = 3.1415926535f;

// Объявление функций

void Cursors();

void Draw_sphere(float x_sp, float y_sp, float r);

void Draw_sphere_traectory(float x_sp, float y_sp, float r);

void Show_plane();

void Axe();

void Aircraft_traectory(float H, float x_end, float y_end, float z_end);

void Aircraft_turn(float H, float V, float pitch, float yaw, float radius, float R_turn);

void Move_Camera(bool flag_console);

//

struct_inter Intersection_sphere(float H, float V, float pitch, float yaw, float x_sp, float z_sp, float R_sp);

struct_inter Not_intersection(float pitch, float yaw, float H, float V);

void Track_aircraft(float x_inter, float y_inter, float z_inter, float H, float pitch, float yaw);

//

float Angle_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

float Disrance_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

void Interface_low(float H, float V, float pitch, float yaw, float x_sphere, float y_sphere, float x_radius);