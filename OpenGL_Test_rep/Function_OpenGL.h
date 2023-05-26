// Подключение заголовочных файлов и библиотек
// Подключение OpenGL и библиотек для работы с ним
#include "glew.h" 
#include "glfw3.h"
#include "gl/gl.h"
#include "gl/glut.h"
#include "ftgl.h"
//#include <ft2build.h>
//#include FT_FREETYPE_H

//
//#include <FTFont.h>
//#include <FTGLPolygonFont.h>
//#include <FTPoint.h>
//

// Подключение стандартных библиотек
#include <iostream>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

// Подключение файла с структурами
#include "Struct_OpenGL.h"

#pragma once

//********************************************************************
// Раздел описания глобальных переменных
//
// Ускорение свободного падения
float GLOBAL_EARTH_ACSELERATION = 9.8f;
// Число PI
float GLOBAL_PI = 3.1415926535f;
//********************************************************************

// Объявление функций для работы с программой
//
//********************************************************************
// Блок - отрисовка объектов на сцене
//********************************************************************
void Cursors();

void Draw_sphere(float x_sp, float y_sp, float r);

void Draw_sphere_traectory(float x_sp, float y_sp, float r);

void Show_plane();

void Axe();

void Aircraft_traectory(float H, float x_end, float y_end, float z_end);

void Aircraft_turn(float H, float V, float pitch, float yaw, float radius, float R_turn);

void Begin_sphere(float H);

void End_sphere(float x, float y, float z);

void Inter_sphere(float x, float y, float z);

void Contact_sphere(float x, float y, float z);

//********************************************************************
// Блок - основные математические расчеты
//********************************************************************

struct_inter Intersection_sphere(float H, float V, float pitch, float yaw, float x_sp, float z_sp, float R_sp);

struct_inter Not_intersection(float pitch, float yaw, float H, float V);

struct_track Track_aircraft(float turn_x, float turn_y, float turn_z, float H, float V, float pitch, float yaw);

struct_inter Contact_aircraft(float inter_x, float inter_y, float inter_z, float H, float V, float pitch, float yaw, float R_turn);

struct_track Track_aircraft(float turn_x, float turn_y, float turn_z, float H, float V, float pitch, float yaw);

//********************************************************************
// Блок - промежуточные математические расчеты
//********************************************************************

float Search_R_turn(float H, float V, float pitch, float yaw);

float Angle_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

float Disrance_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

bool Check_input_data(float A, float B, float C, float x_r, float y_r, float R);

//********************************************************************
// Блок - управление сценой
//********************************************************************

void Move_Camera();

void Interface_low(float H, float V, float pitch, float yaw, float x_sphere, float y_sphere, float x_radius);

int draw_text_1();