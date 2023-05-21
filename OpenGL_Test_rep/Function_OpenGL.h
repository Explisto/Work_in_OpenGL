#include "Struct_OpenGL.h"

// Ïîäêëþ÷åíèå áèáëèîòåê

#include "glew.h" 
#include "glfw3.h"
#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>



#pragma once

// Ðàçäåë ñ îïèñàíèåì ãëîáàëüíûõ êîíñòàíò
//
// Óñêîðåíèå ñâîáîäíîãî ïàäåíèÿ
float GLOBAL_EARTH_ACSELERATION = 9.8f;
// ×èñëî PI
float GLOBAL_PI = 3.1415926535f;

// Îáúÿâëåíèå ôóíêöèé

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

struct_track Track_aircraft(float turn_x, float turn_y, float turn_z, float H, float V, float pitch, float yaw);

struct_contact Contact_aircraft(float inter_x, float inter_y, float inter_z, float H, float V, float pitch, float yaw, float R_turn);

void Track_aircraft(float x_inter, float y_inter, float z_inter, float H, float pitch, float yaw);

//

float Angle_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

float Disrance_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

bool Check_input_data(float A, float B, float C, float x_r, float y_r, float R);

void Interface_low(float H, float V, float pitch, float yaw, float x_sphere, float y_sphere, float x_radius);