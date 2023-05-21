﻿// Main - файл
//

// Подключение заголовочного файла
#include "Function_OpenGL.h"

 // Подключение модулей
#include "Math_OpenGL.cpp"
#include "Interface_OpenGL.cpp"
#include "Camera_OpenGL.cpp"
#include "Look_world_OpenGL.cpp"

// Подключение пространства имен std
using namespace std;

//
// Инициализация структур для хранения данных специальных точек
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
 * @brief Функция построения траектории виража ЛА
 * @param H Начальная высота ЛА
 * @param pitch Угол тангажа ЛА
 * @param yaw Угол рысканья ЛА
 * @param radius Радиус сферы
 * @param R_turn Радиус окружности виража ЛА
***********************************************************************************/
void Aircraft_turn(float H, float V, float pitch, float yaw, float radius, float R_turn)
{
    // Массив точек: первая - на расстоянии радиуса виража от начальной точки, вторая - центр окружности виража ЛА
    float vert_1[] = { 0, 0, H + R_turn / sin((90 - pitch) * GLOBAL_PI / 180), inter.x, inter.y, inter.z + R_turn / sin((90 - pitch) * GLOBAL_PI / 180) };

    // Точки для построения окружности
    float x_rotate, y_rotate, z_rotate = 0;

    // Угол поворота точки на окружности
    float alfa = 0;

    // Счетчик окружности для отрисовки
    float circle_def = 50;

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
    glRotatef(-pitch * sin(pitch * GLOBAL_PI / 180) + pitch * cos(pitch * GLOBAL_PI / 180), 0.0f, 0.0f, 1.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    // Начало рисования окружности - траектории ухода ЛА
    glBegin(GL_LINE_STRIP);
    // Установка цвета траектории
    glColor3f(1.0, 0.0, 0.0);

    // Цикл - нахождение точек окружности
    for (int count_circle = 0; count_circle < int(circle_def); count_circle++)
    {
        if (count_circle > 19)
        {
            // Нахождение угла поворота точки
            alfa = -count_circle / 50.0f * GLOBAL_PI;
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
    for (int count_sphere = 0; count_sphere < int(circle_def); count_sphere++)
    {
        // Нахождение угла поворота точки
        alfa = -count_sphere / 50.0f * GLOBAL_PI;
        // Нахождение координат точки окружности
        x_rotate = cos(alfa) * R_turn;
        y_rotate = sin(alfa) * R_turn;
        // Построение сфер на траектории ЛА
        if ((count_sphere >= 20) && (count_sphere % 10 == 0))
        {
            Draw_sphere_traectory(x_rotate, y_rotate, 0.08); // Вызов функции построения сферы
        }
        if (count_sphere == (int(circle_def) - 1))
        {
            Draw_sphere_traectory(x_rotate, y_rotate, 0.1); // Вызов функции построения сферы
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
    // Подключение вывода кириллицы в консоль
    setlocale(LC_ALL, "Russian");
    //***************************************************************************************

    // Входные (начальные параметры)
    float H_input = 5000.0; // Начальная высота ЛА
    float V_input = 500.0; // Скорость ЛА
    float pitch = -45.0; // Угол тангажа ЛА
    float yaw = 45.0; // Угол рысканья ЛА
    float X_input = 2000.0; // Координата x полусферы
    float Y_input = 2000.0; // Координата y полусферы
    float Radius_input = 2000.0; // Радиус полусферы

    // Преобразованные данные для работы в OpenGL
    float H;
    float V;
    float x_sphere;
    float y_sphere;
    float radius_sphere;

    // Шаг изменения параметров
    float H_delta = 250.0;
    float V_delta = 50.0;
    float Pitch_delta = 1.0;
    float Yaw_delta = 1.0;
    float X_delta = 250.0;
    float Y_delta = 250.0;
    float Radius_delta = 250.0;
    float sign_delta = 1.0;


    bool flag_cross = false; // Метка пересечения траектории ЛА и полусферы

    float R_turn; // Значение радиуса виража
    float n_y; // Значение продольной перегрузки

    float bf_x, bf_y, bf_z; // Буферные переменные

    float cos_roll; // Значение косинуса угла крена

    bool flag_all; // Метка захода в цикл пересчета значений

    // Коэффициенты масштабирования окна
    float coefficient_scale_big = 1000.0;
    float coefficient_scale_small = 100.0;
    // угол между векторами траектории и центра полусферы
    float angle_radius;

    // Указатель на созданный экземпляр окна
    GLFWwindow* window;

    // Размер выходного окна glfw
    int viewportWidth = 600;
    int viewportHeight = 600;

    // Коэффициент масштаба экрана
    float ratio = viewportWidth / viewportHeight;

    // Переменная метка нажатия клавиши смены значений
    bool flag_console = true;

    // Проверка инициализации библиотеки GLFW
    if (!glfwInit())
        return -1;

    // Создание сового окна с заданными размерами
    window = glfwCreateWindow(viewportWidth, viewportHeight, "Aircraft", NULL, NULL);
    // Если окно не создано
    if (!window)
    {
        glfwTerminate(); // Уничтожение окна
        return -1;
    }
    glfwMaximizeWindow(window);
    // Создание контекста окна
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW is not\n";
        return -1;
    }

    glFrustum(-1, 1, -1, 1, 1, 80);

    cout << "===================================================" << endl;
    cout << "!Уход ЛА по круговой траектории!" << endl;
    cout << "===================================================" << endl;

    float buf_h = viewportHeight;
    float buf_w = viewportWidth;
    ///****************************************************************
    // Математические расчеты пересечения заданной траектории и сферы
    ///************************************************************
    ///************************************************************
    // Основной цикл программы, пока не закрыто окно glfw
    while (!glfwWindowShouldClose(window))
    {
        // Отслеживание изменения размера окна
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if ((buf_w != viewportWidth) || buf_h != viewportHeight)
        {
            glViewport(0, 0, viewportWidth, viewportHeight);
            //glLoadIdentity();
            ratio = (float)viewportWidth / (float)viewportHeight;
            //glOrtho(-ratio, ratio, -1, 1, -1, 1);
            glScalef(ratio, ratio, ratio);
            buf_w = viewportWidth;
            buf_h = viewportHeight;
        }
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        // Окончание работы программы при помощи нажатия клавиши Escape
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        if (GetKeyState(VK_NUMPAD0) < 0)
        {
            sign_delta = -sign_delta;
            Sleep(250);
        }
        if (GetKeyState(VK_NUMPAD1) < 0)
        {
            flag_console = true;
            H_input = H_input + (H_delta * sign_delta);
            if (H_input < 1000)
            {
                H_input = 1000;
            }
            if (H_input > 12000)
            {
                H_input = 12000;
            }
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD2) < 0)
        {
            flag_console = true;
            V_input = V_input + (V_delta * sign_delta);
            if (V_input < 150)
            {
                V_input = 150;
            }
            if (V_input > 1000)
            {
                V_input = 1000;
            }
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD3) < 0)
        {
            flag_console = true;
            pitch = pitch + (Pitch_delta * sign_delta);
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD4) < 0)
        {
            flag_console = true;
            yaw = yaw + (Yaw_delta * sign_delta);
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD5) < 0)
        {
            flag_console = true;
            if (Check_input_data((X_input + (X_delta * sign_delta)) / coefficient_scale_big, Y_input / coefficient_scale_big, Radius_input / coefficient_scale_big))
            {
                X_input = X_input + (X_delta * sign_delta);
            }
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD6) < 0)
        {
            flag_console = true;
            if (Check_input_data(X_input / coefficient_scale_big, (Y_input + (Y_delta * sign_delta)) / coefficient_scale_big, Radius_input / coefficient_scale_big))
            {
                Y_input = Y_input + (Y_delta * sign_delta);
            }
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD7) < 0)
        {
            flag_console = true;
            if (Check_input_data(X_input / coefficient_scale_big, Y_input / coefficient_scale_big, (Radius_input + (Radius_delta * sign_delta)) / coefficient_scale_big))
            {
                Radius_input = Radius_input + (Radius_delta * sign_delta);
            }
            if (Radius_input < 500)
            {
                Radius_input = 500;
            }
            if (Radius_input > 5000)
            {
                Radius_input = 5000;
            }
            Sleep(50);
        }

        if (flag_console == true)
        {
            // Пересчет коэффициентов
            H = H_input / coefficient_scale_big;
            V = V_input / coefficient_scale_small;
            x_sphere = X_input / coefficient_scale_big;
            y_sphere = Y_input / coefficient_scale_big;
            radius_sphere = Radius_input / coefficient_scale_big;

            inter = Intersection_sphere(H, V, pitch, yaw, x_sphere, y_sphere, radius_sphere);
            //

            flag_all = inter.flag_inter;

            cos_roll = atanf(tanf(yaw * GLOBAL_PI / 180) / cosf(pitch * GLOBAL_PI / 180));

            cos_roll = cosf(cos_roll);

            cout << "Косинус угла крена = " << cos_roll << ";" << endl;

            if ((cos_roll == 1) || (cos_roll == 0) || (cos_roll == -1))
            {
                R_turn = 0;
                cout << "ВИРАЖ НЕВОЗМОЖЕН!!! НЕДОПУСТИМЫЙ УГОЛ КРЕНА!!!" << endl;
            }
            else
            {
                n_y = 1 / cos_roll;
                R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));
                R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));
                cout << "Радиус виража = " << R_turn << " километров;" << endl;
            }

            angle_radius = Angle_two_vectors(x_sphere, -y_sphere, 0, inter.x, inter.y, 0);

            //********************************************************************************

            if (inter.flag_inter == true)
            {
                bf_x = inter.x;
                bf_y = inter.y;
                bf_z = inter.z;
                inter = Intersection_sphere(H + R_turn / sin((90 - pitch) * GLOBAL_PI / 180), V, pitch, yaw, x_sphere, y_sphere, cos(angle_radius * GLOBAL_PI / 180) * (radius_sphere + R_turn));
                turn.x = inter.x;
                turn.y = inter.y;
                turn.z = inter.z;
                inter = Contact_aircraft(turn.x, turn.y, turn.z, H, V, pitch, yaw, R_turn);
                contact.x = inter.x;
                contact.y = inter.y;
                contact.z = inter.z;
                inter.x = bf_x;
                inter.y = bf_y;
                inter.z = bf_z;
                track = Track_aircraft(turn.x, turn.y, turn.z, H, V, pitch, yaw);
            }

            cout << "Пересечение со сферой - ";
            if (flag_all == true)
            {
                cout << "Да;" << endl;
                cout << "===================================================" << endl;
                cout << "Координаты точки пересечения траектории ЛА и сферы:" << endl;
                cout << "x_inter = " << inter.x << ";" << endl;
                cout << "y_inter = " << inter.y << ";" << endl;
                cout << "z_inter = " << inter.z << ";" << endl;
                cout << "===================================================" << endl;
                cout << "Координаты центра окружности ухода ЛА:" << endl;
                cout << "x_turn = " << turn.x << ";" << endl;
                cout << "y_turn = " << turn.y << ";" << endl;
                cout << "z_turn = " << turn.z << ";" << endl;
                cout << "===================================================" << endl;
                cout << "Координаты точки пересечения траектории ЛА и полусферы:" << endl;
                cout << "x_contact = " << contact.x << ";" << endl;
                cout << "y_contact = " << contact.y << ";" << endl;
                cout << "z_contact = " << contact.z << ";" << endl;
                cout << "===================================================" << endl;
                cout << "Координаты точки начала ухода ЛА по круговой траектории:" << endl;
                cout << "x_track = " << track.x << ";" << endl;
                cout << "y_track = " << track.y << ";" << endl;
                cout << "z_track = " << track.z << ";" << endl;
                cout << "===================================================" << endl;
            }
            else
            {
                cout << "Нет;" << endl;
            }
            cout << "===================================================" << endl;

            //********************************************************************************
        }
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        // Установка цвета фона
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Очистка буфера цвета и глубин
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if ((flag_all == true) && (R_turn != 0))
        {
            // Сохранение матрицы вида в стек
            glPushMatrix();
            // Функция управления камерой
            Move_camera(flag_console);
            // Отрисовка осей
            Axe();
            // Сфера - начала траектории ЛА
            Begin_sphere(H);
            // Отрисовка направляющих стрелок на осях
            Cursors();
            // Сфера - пересечение траектории и сферы
            Inter_sphere(inter.x, inter.y, inter.z);
            // Сфера - пересечение траектории и сферы
            Contact_sphere(contact.x, contact.y, contact.z);
            // Рисование полусферы
            Draw_sphere(x_sphere, -y_sphere, radius_sphere);
            // Отрисовка плоскости
            Show_plane();
            // Отображение траектории ЛА
            Aircraft_traectory(H, inter.x, inter.y, inter.z);
            // Условие, если пересечение траектории со сферой происходит за основной плоскостью
            if (inter.z >= 0)
            {
                // Отрисовка полуокружности ухода ЛА
                Aircraft_turn(H, V, pitch, yaw, radius_sphere, R_turn);
            }
            else
            {
                End_sphere(inter.x, inter.y, inter.z);
            }
            // Возвращение матрицы из стека
            glPopMatrix();
        }
        else
        {
            // Сохранение матрицы вида в стек
            glPushMatrix();
            // Функция управления камерой
            Move_camera(flag_console);
            // Отрисовка осей
            Axe();
            // Сфера начала траектории ЛА
            Begin_sphere(H);
            // Отрисовка направляющих стрелок на осях
            Cursors();
            // Рисование полусферы
            Draw_sphere(x_sphere, -y_sphere, radius_sphere);
            // Отрисовка плоскости
            Show_plane();
            // Нахождение координат конечной точки движения ЛА
            inter = Not_intersection(pitch, yaw, H, V);
            // Построение траектории ЛА
            Aircraft_traectory(H, inter.x, inter.y, inter.z);
            // Построение конечной точки ЛА
            End_sphere(inter.x, inter.y, inter.z);
            // Возвращение матрицы из стека
            glPopMatrix();
        }

        // Окончание обработки новых значений
        flag_console = false;

        // Смена буфера
        glfwSwapBuffers(window);

        // Отслеживание событий внутри окна
        glfwPollEvents();
    }
    // Уничтожение окна
    glfwTerminate();
    // Окончание программы
    return 0;
}