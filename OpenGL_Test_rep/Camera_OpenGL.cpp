// Подключение заголовочного файла
#include "Function_OpenGL.h"

// Структура - координаты камеры в пространстве
struct struct_position_camera {
    float x = 12;
    float y = -12;
    float z = -10;
};

// Инициализация структуры
struct_position_camera pos;
// Параметры для работы с камерой
// Параметры поворота и углов ориентации
float theta = 0.0f;
float turn_x = 0;
float turn_y = 0;
float turn_z = 0;

/***********************************************************************************
 * @brief Функция движения камеры по сцене
 * @return Ничего
***********************************************************************************/
void Move_camera()
{
    // Начальный разворот камеры на сцену
    glRotatef(-45, 1, 0, 0);
    glRotatef(-45, 0, 0, 1);

    // Блок - отслеживания действий пользователя по клавишам
    // Если нажата клавиша "Стрелка вниз"
    // Вращение вокруг оси oX
    if (GetKeyState(VK_UP) < 0)
    {
        turn_x += 0.1f;
    }
    // Далее - аналогично
    if (GetKeyState(VK_DOWN) < 0)
    {
        turn_x -= 0.1f;
    }
    if (GetKeyState('Q') < 0)
    {
        turn_y += 0.1f;
    }
    if (GetKeyState('E') < 0)
    {
        turn_y -= 0.1f;
    }
    if (GetKeyState(VK_LEFT) < 0)
    {
        turn_z += 0.1f;
    }
    if (GetKeyState(VK_RIGHT) < 0)
    {
        turn_z -= 0.1f;
    }
    // Нахождение величины угла поворота относительно соответствующей оси
    float angle_x = -turn_x / 180 * GLOBAL_PI;
    float angle_y = -turn_x / 180 * GLOBAL_PI;

    // Величина перемещения камеры
    float speed_x = 0;
    float speed_y = 0;
    float speed_z = 0;

    // Блок - перемещение камеры относительно осей
    // Если нажата клавиша "W"
    // Перемещение вперед
    if (GetKeyState('W') < 0)
    {
        speed_y = 0.01f;
    }
    // Далее - аналогично
    if (GetKeyState('S') < 0)
    {
        speed_y = -0.01f;
    }

    if (GetKeyState('A') < 0)
    {
        speed_x = -0.01f;
    }
    if (GetKeyState('D') < 0)
    {
        speed_x = 0.01f;
    }

    if (GetKeyState('Z') < 0)
    {
        speed_z = 0.01f;
    }

    if (GetKeyState('C') < 0)
    {
        speed_z = -0.01f;
    }
    // Если пользователь нажимал клавишу
    if ((speed_x != 0) || (speed_y != 0) || (speed_z != 0))
    {
        // Изменение координат камеры
        pos.x += speed_x;
        pos.y += speed_y;
        pos.z += speed_z;
    }
    // Перемещение камеры иее поворот исходя из команд пользователя
    glTranslatef(-pos.x, -pos.y, pos.z);
    glRotatef(-turn_x, 1, 0, 0);
    glRotatef(-turn_y, 0, 1, 0);
    glRotatef(-turn_z, 0, 0, 1);
}