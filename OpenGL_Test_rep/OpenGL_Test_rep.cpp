// OpenGL_Test_rep.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// Подключение заголовочного файла
#include "Function_OpenGL.h"

 // Подключение модулей
#include "Math_OpenGL.cpp"
#include "Interface_OpenGL.cpp"
#include "Camera_OpenGL.cpp"
#include "Look_world_OpenGL.cpp"

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

/***********************************************************************************
 * @brief Создание траектории полета ЛА
 * @return Ничего
***********************************************************************************/
void Aircraft_traectory(float H)
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
    float vert_1[] = { 0, 0, H + R_turn / sin((90 - pitch) * M_PI / 180), inter.x, inter.y, inter.z + R_turn / sin((90 - pitch) * M_PI / 180) };

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
            Aircraft_traectory(H);
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
            //Aircraft_turn(H);
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