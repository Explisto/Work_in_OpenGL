#include "Struct_OpenGL.h"

// Подключение библиотек

#include "glew.h" 
#include "glfw3.h"
#include <iostream>
#include <windows.h>
#include <gl/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>



#pragma once

//
void Cursors();

void Draw_sphere(float x_sp, float y_sp, float r);

void Draw_sphere_traectory(float x_sp, float y_sp, float r);

void Show_plane();

void Axe();

void Aircraft_traectory(float H);

void Aircraft_turn(float H, float pitch, float yaw, float radius, float R_turn);

//

struct_inter Intersection_sphere(float H, float V, float pitch, float yaw, float x_sp, float z_sp, float R_sp);

struct_inter Not_intersection(float pitch, float yaw, float H);

//

//float search_point(float A, float B, float C, float D, float m, float n, float p, float H);

void Track_aircraft(float x_inter, float y_inter, float z_inter, float H, float pitch, float yaw);

//

float Angle_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

float Disrance_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);