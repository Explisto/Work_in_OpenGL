// Подключение заголовочного файла
#include "Function_OpenGL.h"

typedef struct struct_position_camera {
    float x = 8;
    float y = -8;
    float z = -10;
};

struct_position_camera pos;
// Параметры для работы с камерой
float theta = 0.0f;
float turn_x = 0;
float turn_z = 0;

/*
/***********************************************************************************
 * @brief Функция движения камеры по сцене
 * @return Ничего
***********************************************************************************/
void Move_camera()
{

    glRotatef(-45, 1, 0, 0);
    glRotatef(-45, 0, 0, 1);

    if (GetKeyState(VK_UP) < 0)
    {
        turn_x += 0.1f;
    }
    if (GetKeyState(VK_DOWN) < 0)
    {
        turn_x -= 0.1f;
    }
    if (GetKeyState(VK_LEFT) < 0)
    {
        turn_z += 0.1f;
    }
    if (GetKeyState(VK_RIGHT) < 0)
    {
        turn_z -= 0.1f;
    }

    float angle = -turn_x / 180 * M_PI;

    float speed = 0;

    float speed_z = 0;

    if (GetKeyState('W') < 0)
    {
        speed = 0.01f;
    }

    if (GetKeyState('S') < 0)
    {
        speed = -0.01f;
    }

    if (GetKeyState('A') < 0)
    {
        speed = -0.01f;
        angle += M_PI * 0.5f;
    }
    if (GetKeyState('D') < 0)
    {
        speed = -0.01f;
        angle -= M_PI * 0.5f;
    }
    /*
    if (GetKeyState('Q') < 0)
    {
        speed = -0.01f;
    }
    if (GetKeyState('E') < 0)
    {
        speed = -0.01f;
    }
    */
    if (speed != 0)
    {
        pos.x += sin(angle) * speed;
        pos.y += cos(angle) * speed;
        //pos.z += cos(angle) * speed;
    }

    glTranslatef(-pos.x, -pos.y, pos.z);
    glRotatef(-turn_x, 1, 0, 0);
    glRotatef(-turn_z, 0, 0, 1);
}