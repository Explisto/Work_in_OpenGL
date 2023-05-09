#include "Struct_OpenGL.h"

#pragma once

struct_inter Intersection_sphere(float H, float V, float pitch, float yaw, float x_sp, float z_sp, float R_sp);

float search_point(float A, float B, float C, float D, float m, float n, float p, float H);

//float* vertex_complection(float x_t, float y_t, float z_t);

void Draw_sphere_traectory(float x_sp, float y_sp, float r);

struct_inter Not_intersection(float pitch, float yaw, float H);

void Track_aircraft(float x_inter, float y_inter, float z_inter, float H, float pitch, float yaw);

float Angle_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);

float Disrance_two_vectors(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2);