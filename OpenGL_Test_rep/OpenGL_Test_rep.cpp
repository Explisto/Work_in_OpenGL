// OpenGL_Test_rep.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// Подключение библиотек

#include "glew.h" 
#include "glfw3.h"
#include <iostream>
#include <windows.h>
#include <gl/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>

 // Подключение модулей
#include "Math_OpenGL.cpp"
#include "Interface_OpenGL.cpp"
#include "Camera_OpenGL.cpp"

// Подключение заголовочных файлов
#include "Function_OpenGL.h"

using namespace std;

//
// Раздел с описанием глобальных констант
//
// Ускорение свободного падения
float GLOBAL_EARTH_ACSELERATION = 9.8f;

//
// Инициализация структур для хранения данных специальных точек
//
// Инициализация ???
struct_turn init;
// Структура для координат точки пересечения траектории ЛА и сферы
// В случае отстутствия точек пересечения - координаты крайней точки траектории ЛА
struct_inter inter;
// Структура для координат начальной точки виража ЛА
struct_track track;
// Структура для координат точки центра окружности виража ЛА
struct_turn turn;
// Структура для координат точки пересечения окружности виража ЛА и сферы
struct_contact contact;


/**********************************************************************************
* @brief Генерация плоскости, на которой находится полусфера
* @return Ничего
**********************************************************************************/
void Show_plane()
{
    // Инициализация элементов плоскости - двух линий
    float vert_line_1[] = { 0,0,0, 0,-11,0 };
    float vert_line_2[] = { 0,0,0, 11,0,0 };

    // Метка, что будет использован массив вершин
    glEnableClientState(GL_VERTEX_ARRAY);
    // Сохранение данных из массива вершин
    glVertexPointer(3, GL_FLOAT, 0, &vert_line_1);

    // Цикл создания линий сетки
    for (int count_line_1 = 0; count_line_1 < 12; count_line_1++)
    {
        // Сохранение текущей матрицы в стек
        glPushMatrix();
        // Установка цвета примитива
        glColor3f(0, 1, 0);
        // Перенос координат линии
        glTranslatef(count_line_1, 0, 0);
        // Создание примитива в виде линии
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        // Возвращение матрицы из стека
        glPopMatrix();
    }

    // Метка, что массив вершин больше не будет использоваться
    glDisableClientState(GL_VERTEX_ARRAY);

    // Метка, что будет использован массив вершин
    glEnableClientState(GL_VERTEX_ARRAY);
    // Сохранение данных из массива вершин
    glVertexPointer(3, GL_FLOAT, 0, &vert_line_2);
    
    for (int count_line_2 = 0; count_line_2 < 12; count_line_2++)
    {
        // Сохранение текущей матрицы в стек
        glPushMatrix();
        // Установка цвета примитива
        glColor3f(1, 0.8, 0);
        // Перенос координат линии
        glTranslatef(0, -count_line_2, 0);
        // Создание примитива в виде линии
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        // Возвращение матрицы из стека
        glPopMatrix();
    }
    // Метка, что массив вершин больше не будет использоваться
    glDisableClientState(GL_VERTEX_ARRAY);
}

/***********************************************************************************
 * @brief Создание осей системы координат
 * @return Ничего
***********************************************************************************/
void Axe()
{
    // Массивы точек, устанавливающие оси СК
    float vert_x[] = { 0,0,0, 12,0,0 };
    float vert_y[] = { 0,0,0, 0,-12,0 };
    float vert_z[] = { 0,0,0, 0,0,12 };

    // Ширина линий
    glLineWidth(10);

    // Метка, что будет использован массив вершин
    glEnableClientState(GL_VERTEX_ARRAY);
    // Сохранение данных из массива вершин
    glVertexPointer(3, GL_FLOAT, 0, &vert_x);
    
    // Сохранение текущей матрицы в стек
    glPushMatrix();
    // Установка цвета примитива
    glColor3f(0, 0, 1);
    // Создание примитива в виде линии
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    // Возвращение матрицы из стека
    glPopMatrix();

    // Далее - аналогично для остальных двух осей
    //******************************************
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert_y);

    glPushMatrix();
    glColor3f(0, 0, 1);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    glPopMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert_z);

    glPushMatrix();
    glColor3f(0, 0, 1);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    glPopMatrix();
    //******************************************
    
    // Ширина линий
    glLineWidth(1);
}

/***********************************************************************************
 * @brief Создание траектории полета ЛА
 * @return Ничего
***********************************************************************************/
void Aircraft_turn(float H)
{
    // Настройка вершин
    float vert_x[] = { 0,0,H, inter.x, inter.y, inter.z };

    // Размер линии
    glLineWidth(10);

    // Метка, что будет использован массив вершин
    glEnableClientState(GL_VERTEX_ARRAY);
    // Сохранение данных из массива вершин
    glVertexPointer(3, GL_FLOAT, 0, &vert_x);

    // Сохранение текущей матрицы в стек
    glPushMatrix();
    // Установка цвета примитива
    glColor3f(0, 0.8, 0);
    // Создание примитива в виде линии
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    // Возвращение матрицы из стека
    glPopMatrix();
}

/***********************************************************************************
 * @brief Функция построения траектории виража ЛА
 * @param H Начальная высота ЛА
 * @param pitch Угол тангажа ЛА
 * @param yaw Угол рысканья ЛА
 * @param radius Радиус сферы
 * @param R_turn Радиус окружности виража ЛА
***********************************************************************************/
void Aircraft_turn(float H, float pitch, float yaw, float radius, float R_turn)
{

    // Массив точек: первая - на расстоянии радиуса виража от начальной точки, вторая - центр окружности виража ЛА
    float vert_1[] = {0, 0, H + R_turn / sin((90-pitch) * M_PI / 180), inter.x, inter.y, inter.z + R_turn / sin((90 - pitch) * M_PI / 180)};

    // Точки для построения окружности
    float x_rotate, y_rotate, z_rotate = 0;

    // Угол поворота точки на окружности
    float alfa;

    // Размер линии
    glLineWidth(10);
    // Метка, что будет использован массив вершин
    glEnableClientState(GL_VERTEX_ARRAY);
    // Сохранение данных из массива вершин
    glVertexPointer(3, GL_FLOAT, 0, &vert_1);

    // Сохранение текущей матрицы в стек
    glPushMatrix();
    // Установка цвета примитива
    glColor3f(1, 0, 0);
    // Создание примитива в виде линии - верхняя траектория ЛА
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    // Возвращение матрицы из стека
    glPopMatrix();

    // Установка размера точки - начала ухода ЛА
    glPointSize(20);
    glBegin(GL_POINTS);
        
        // Установка цвета примитива
        glColor3d(0, 1, 0);
        // Координаты точки начала ухода ЛА
        glVertex3d(track.x, track.y, track.z);

    glEnd();

    // Установка размера точки - точка пересечения сфер
    glPointSize(20);
    glBegin(GL_POINTS);
        
        // Установка цвета примитива
        glColor3d(0.8, 1, 0.5);
        // Координаты точки контакта сфер
        glVertex3d(contact.x, contact.y, contact.z);

    glEnd();

    // Установка размера точки - точка центра окружности ухода ЛА
    glPointSize(20);
    glBegin(GL_POINTS);
        
        // Установка цвета примитива
        glColor3d(1, 0.8, 0);
        // Координаты центра окружности ухода ЛА
        glVertex3d(turn.x, turn.y, turn.z);
    
    glEnd();

    // Построение траектории ухода ЛА
    glColor3f(0.1f, 1.0f, 0.2f);
    
    // Сохранение текущей матрицы в стек
    glPushMatrix();

    // Перемещение в точку начала построения окружности
    glTranslatef(turn.x, turn.y, turn.z);
    // Поворот окружности относительно оси oX
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    // Поворот окружности на угол рысканья
    glRotatef(-(90 - yaw), 0.0f, 1.0f, 0.0f);
    // Поворот окружности на угол танагажа
    glRotatef(-pitch - 10, 0.0f, 0.0f, 1.0f);
    //glRotatef(10, 0.0f, 0.0f, 1.0f);
    

    // Начало рисования окружности - траектории ухода ЛА
    glBegin(GL_LINE_STRIP);
    
    // Цикл - нахождение точек окружности
    for (int count_circle = 0; count_circle < 60; count_circle++)
    {
        if (count_circle > 19)
        {
            // Очистка буфера глубины
            glClear(GL_COLOR_BUFFER_BIT);
            // Нахождение угла поворота точки
            alfa = -count_circle / 50.0f * M_PI;
            // Нахождение координат точки окружности
            x_rotate = cos(alfa) * R_turn;
            y_rotate = sin(alfa) * R_turn;
            // Отображение точки
            glVertex3f(x_rotate, y_rotate, 0);
        }
        else
        {
            // Нахождение координат точки окружности
            x_rotate = cos(alfa) * R_turn;
            y_rotate = sin(alfa) * R_turn;
        }
    }
    glEnd();
    // Цикл - построение сфер на траектории
    for (int count_sphere = 0; count_sphere < 60; count_sphere++)
    {
        // Нахождение угла поворота точки
        alfa = -count_sphere / 50.0f * M_PI;
        // Нахождение координат точки окружности
        x_rotate = cos(alfa) * R_turn;
        y_rotate = sin(alfa) * R_turn;
        // Построение сфер на траектории ЛА
        if (((count_sphere % 10 == 0) || (count_sphere == 49)) && (count_sphere > 19))
        {
            Draw_sphere_traectory(x_rotate, y_rotate, 0.05); // Вызов функции построения сферы
        }
    }
    // Возвращение матрицы из стека
    glPopMatrix();
    

}

/***********************************************************************************
 * @brief Создание стрелок для осей координат
 * @return Ничего
***********************************************************************************/
void Cursors()
{
    // Настройка координат пирамид
    float pyramid_x[] = { 13, 0, 0, 12, 0.5, -0.5, 12, -0.5, -0.5, 12, -0.5, 0.5, 12, 0.5, 0.5, 12, 0.5, -0.5};
    float pyramid_y[] = { 0, 0, 13, -0.5, 0.5, 12, -0.5, -0.5, 12, 0.5, -0.5, 12, 0.5, 0.5, 12, -0.5, 0.5, 12};
    float pyramid_z[] = { 0, -13, 0, 0.5, -12, -0.5, -0.5, -12, -0.5, -0.5, -12, 0.5, 0.5, -12, 0.5, 0.5, -12, -0.5};

    // Метка, что будет использован массив вершин
    glEnableClientState(GL_VERTEX_ARRAY);
    // Сохранение данных из массива вершин для первой пирамиы
    glVertexPointer(3, GL_FLOAT, 0, &pyramid_x);
    // Установка цвета примитива
    glColor3f(0.5f, 0.5f, 0.1f);
    // Создание примитива в виде треугольника
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    // Далее - аналогично для остальных двух осей
    //*****************************************************
    glVertexPointer(3, GL_FLOAT, 0, &pyramid_y);
    glColor3f(0.5f, 0.5f, 0.1f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    glVertexPointer(3, GL_FLOAT, 0, &pyramid_z);
    glColor3f(0.5f, 0.5f, 0.1f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    //*****************************************************

    // Метка об отключении использования массива вершин
    glDisableClientState(GL_VERTEX_ARRAY);
}

/***********************************************************************************
 * @brief Создание полусферы и сетки для нее
 * @param x_sp Координата центра сферы по оси oX
 * @param y_sp Координата центра сферы по оси oY
 * @param r Радиус сферы
 * @return Ничего
***********************************************************************************/
void Draw_sphere(float x_sp, float y_sp, float r)
{

    float di = 0.02;
    float dj = 0.04;
    float db = di * 2 * M_PI;
    float da = dj * M_PI;
    float p_1, p_2, p_3, p_4;

    // Горизонтальная плоскость
    for (float i = 0.0; i < 1.0; i += di)
    {
        // Вертикальная плоскость
        for (float j = 0.5; j < 1.0; j += dj)
        {
            float b = i * 2 * M_PI;
            float a = (j - 0.5) * M_PI;

            glColor3f(1.0f, 1.0f, 0.0f);
            // Нормализация координат вектора
            glNormal3f(
                x_sp + cos(a + da / 2) * cos(b + db / 2),
                y_sp + cos(a + da / 2) * sin(b + db / 2),
                sin(a + da / 2));

            // Создание четырехугольника для полусферы
            glBegin(GL_QUADS);

            // Нахождение координат точки P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                y_sp + r * cos(a) * sin(b),
                r * sin(a));
            // Нахождение координат точки P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                y_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            // Нахождение координат точки P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                y_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            // Нахождение координат точки P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                y_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();

            // Создание сетки
            glBegin(GL_LINE_STRIP);

            glColor3f(1.0f, 0.0f, 0.0f);
            // Для точки P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                y_sp + r * cos(a) * sin(b),
                r * sin(a));
            // Для точки P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                y_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            // Для точки P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                y_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            // Для точки P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                y_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();
            
        }
    }
}

/***********************************************************************************
 * @brief Создание сферы на траектории ЛА
 * @param x_sp Координата центра сферы по оси oX
 * @param y_sp Координата центра сферы по оси oY
 * @param r Радиус сферы
 * @return Ничего
***********************************************************************************/
void Draw_sphere_traectory(float x_sp, float y_sp, float r)
{

    float di = 0.02;
    float dj = 0.04;
    float db = di * 2 * M_PI;
    float da = dj * M_PI;
    float p_1, p_2, p_3, p_4;

    // Горизонтальная плоскость
    for (float i = 0.0; i < 1.0; i += di)
    {
        // Вертикальная плоскость
        for (float j = 0.0; j < 1.0; j += dj)
        {
            float b = i * 2 * M_PI;
            float a = (j - 0.5) * M_PI;

            glColor3f(1.0f, 0.0f, 0.0f);
            // Нормализация координат вектора
            glNormal3f(
                x_sp + cos(a + da / 2) * cos(b + db / 2),
                y_sp + cos(a + da / 2) * sin(b + db / 2),
                sin(a + da / 2));

            // Создание четырехугольника для полусферы
            glBegin(GL_QUADS);

            // Нахождение координат точки P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                y_sp + r * cos(a) * sin(b),
                r * sin(a));
            // Нахождение координат точки P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                y_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            // Нахождение координат точки P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                y_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            // Нахождение координат точки P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                y_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();

        }
    }
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
    float distance;

    // Нахождение расстояния между двумя точками
    distance = sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2) + pow((z_1 - z_2), 2));

    return distance;
}

/***********************************************************************************
 * @brief Основное тело программы
 * @return Ничего
***********************************************************************************/
int main(void)
{
    float H;
    float V;
    float pitch;
    float yaw;
    float x_sphere;
    float y_sphere;
    float radius_sphere;
    bool flag_cross;

    float R_turn;
    float n_y;

    float bf_x, bf_y, bf_z;

    float cos_roll;

    float coefficient_scale_big = 1000;
    float coefficient_scale_small = 100;

    float angle_radius;
    GLFWwindow* window;

    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 1200, "Aircraft", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW is not\n";
        return -1;
    }

    glFrustum(-1, 1, -1, 1, 2,80);

    /****************************************************************
    // Математические расчеты пересечения заданной траектории и сферы
    // **************************************************************
    H = 3;
    V = 2;
    pitch = -45;
    yaw = 45;
    x_sphere = 2;
    y_sphere = 2;
    radius_sphere = 2;
    //**************************************************************
    *///************************************************************

    ///****************************************************************
    // Математические расчеты пересечения заданной траектории и сферы
    // **************************************************************
    H = 3000;
    V = 200;
    pitch = -45;
    yaw = 30;
    x_sphere = 2000;
    y_sphere = 2000;
    radius_sphere = 200;
    //**************************************************************
    //*///************************************************************

    //
    H = 3000 / coefficient_scale_big;
    V = 200 / coefficient_scale_small;
    pitch = -45;
    yaw = 30;
    x_sphere = 2000 / coefficient_scale_big;
    y_sphere = 2000 / coefficient_scale_big;
    radius_sphere = 200 / coefficient_scale_small;
    //

    inter = Intersection_sphere(H, V, pitch, yaw, x_sphere, y_sphere, radius_sphere);

    cout << "x = " << inter.x << endl;
    cout << "y = " << inter.y << endl;
    cout << "z = " << inter.z << endl;
    cout << "flag = " << inter.flag_inter << endl;

    //********************************************************************************

    /*
    //cos_roll = pow(cos(yaw * M_PI / 180), 2) - pow(cos(pitch * M_PI / 180), 2);
    //cout << cos_roll << "cos" << endl;

    //cos_roll = 1 - cos_roll;
    //cout << cos_roll << "cos" << endl;
    //cos_roll = sqrt(cos_roll);
    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    // cos = 0

    //cout << cos_roll << "cos" << endl;

    if ((cos_roll == 1) || (cos_roll == 0) || (cos_roll == -1))
    {
        R_turn = 2;
    }
    else
    {
        n_y = 1 / cos_roll;
        R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));
    }
    */

    n_y = 1.5;

    R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));

    //R_turn = 2;

    cout << R_turn << "R_VIRAZHE" << endl;


    angle_radius = Angle_two_vectors(x_sphere, -y_sphere, 0, inter.x, inter.y, 0);

    cout << angle_radius << "angle_VIRAZHE" << endl;

    //********************************************************************************

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Очистка буфера цвета и глубины
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //cout << flag_cross << endl;
        
        if (inter.flag_inter == true)
        {
            glPushMatrix();
            Move_camera();
            Axe();
            Cursors();
            Draw_sphere(x_sphere, -y_sphere, radius_sphere);
            Show_plane();
            Aircraft_turn(H);
            bf_x = inter.x;
            bf_y = inter.y;
            bf_z = inter.z;
            inter = Intersection_sphere(H + R_turn / sin((90-pitch) * M_PI / 180), V, pitch, yaw, x_sphere, y_sphere, cos(angle_radius * M_PI / 180) * (radius_sphere + R_turn));
            turn.x = inter.x;
            turn.y = inter.y;
            turn.z = inter.z;
            inter.x = bf_x;
            inter.y = bf_y;
            inter.z = bf_z;
            bf_x = inter.x;
            bf_y = inter.y;
            bf_z = inter.z;
            inter = Intersection_sphere(H + R_turn / sin((90 - pitch) * M_PI / 180), V, pitch, yaw, x_sphere, y_sphere, radius_sphere);
            contact.x = inter.x;
            contact.y = inter.y;
            contact.z = inter.z;
            inter.x = bf_x;
            inter.y = bf_y;
            inter.z = bf_z;
            track = Track_aircraft(turn.x, turn.y, turn.z, H, V, pitch, yaw);
            Aircraft_turn(H, pitch, yaw, radius_sphere, R_turn);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            Move_camera();
            Axe();
            Cursors();
            Draw_sphere(x_sphere, -y_sphere, radius_sphere);
            Show_plane();
            //inter = Not_intersection(pitch, yaw, H);
            bf_x = H * cos(pitch * M_PI / 180) * sin(yaw * M_PI / 180);
            bf_y = -H * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
            bf_z = H + H * sin(pitch * M_PI / 180);
            inter.x = bf_x;
            inter.y = bf_y;
            inter.z = bf_z;
            //cout << "x_no = " << inter.x << endl;
            //cout << "y_no = " << inter.y << endl;
            //cout << "z_no = " << inter.z << endl;
            Aircraft_turn(H);
            glPopMatrix();
        }
        //
        //

        //
        // Смена буфера
        glfwSwapBuffers(window);

        // 
        glfwPollEvents();
    }

    // Очистка буфера
    glfwTerminate();
    return 0;
}