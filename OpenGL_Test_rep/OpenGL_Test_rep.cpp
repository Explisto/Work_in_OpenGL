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

    // Коэффициент окружности для отрисовки
    float circle_def = R_turn * 40;

    // Размер линии
    glLineWidth(10);
    // Метка, что будет использован массив вершин
    glEnableClientState(GL_VERTEX_ARRAY);
    // Сохранение данных из массива вершин
    glVertexPointer(3, GL_FLOAT, 0, &vert_1);

    //glPrintl();

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
    glPointSize(40);
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
    glColor3f(0, 0.8, 0);

    // Цикл - нахождение точек окружности
    for (int count_circle = 0; count_circle < int(circle_def); count_circle++)
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
    for (int count_sphere = 0; count_sphere < int(circle_def); count_sphere++)
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
    setlocale(LC_ALL, "Russian");
    float H; // Начальная высота ЛА
    float V; // Скорость ЛА
    float pitch; // Угол тангажа ЛА
    float yaw; // Угол рысканья ЛА
    float x_sphere; // Координата x полусферы
    float y_sphere; // Координата y полусферы
    float radius_sphere; // Радиус полусферы
    bool flag_cross; // Метка пересечения траектории ЛА и полусферы

    float R_turn; // Значение радиуса виража
    float n_y; // Значение продольной перегрузки

    float bf_x, bf_y, bf_z; // Буферные переменные

    float cos_roll; // Значение 

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

    cout << "===================================================" << endl;
    cout << "!Уход ЛА по круговой траектории!" << endl;
    cout << "===================================================" << endl;

    ///****************************************************************
    // Математические расчеты пересечения заданной траектории и сферы
    // **************************************************************
    H = 3000;
    V = 500;
    pitch = -45;
    yaw = 30;
    x_sphere = 2000;
    y_sphere = 2000;
    radius_sphere = 200;
    //**************************************************************
    //*///************************************************************
    cout << "Входные данные для работы программы:" << endl;
    cout << "Начальная высота ЛА:" << H << " метров;" <<endl;
    cout << "Скорость ЛА: " << V << " км/ч;" << endl;
    cout << "Угол тангажа ЛА: " << pitch << " градусов;" << endl;
    cout << "Угол рысканья ЛА: " << yaw << " градусов;" << endl;
    cout << "Координаты центра полусферы по оси oX: " << x_sphere << " метров;" << endl;
    cout << "Координаты центра полусферы по оси oY: " << y_sphere << " метров;" << endl;
    cout << "Радиус полусферы: " << radius_sphere << " метров;" << endl;
    cout << "===================================================" << endl;
    //
    H = H / coefficient_scale_big;
    V = V / coefficient_scale_small;
    x_sphere = x_sphere / coefficient_scale_big;
    y_sphere = y_sphere / coefficient_scale_big;
    radius_sphere = radius_sphere / coefficient_scale_small;
    //

    inter = Intersection_sphere(H, V, pitch, yaw, x_sphere, y_sphere, radius_sphere);
    cout << "===================================================" << endl;
    cout << "Точка пересечения траектории ЛА и сферы:" << endl;
    cout << "Произошло ли пересечение со сферой? - ";
    if (inter.flag_inter == true)
    {
        cout << "Да;" << endl;
    }
    else
    {
        cout << "Нет;" << endl;
    }
    cout << "x_inter = " << inter.x << ";" << endl;
    cout << "y_inter = " << inter.y << ";" << endl;
    cout << "z_inter= " << inter.z << ";" << endl;
    cout << "===================================================" << endl;

    //********************************************************************************

    
    //cos_roll = sqrt(1 - pow(cos(yaw * M_PI / 180), 2) - pow(cos(pitch * M_PI / 180), 2));

    cos_roll = 0.5;

    cout << "Косинус угла крена = " << cos_roll << ";" <<endl;

    if ((cos_roll == 1) || (cos_roll == 0) || (cos_roll == -1))
    {
        R_turn = 0;
        cout << "ВИРАЖ НЕВОЗМОЖЕН!!! НЕДОПУСТИМЫЙ УГОЛ КРЕНА!!!" << endl;
    }
    else
    {
        n_y = 1 / cos_roll;
        R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));
    }

    R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));

    cout << "Радиус виража = "<< R_turn << " метров;" <<endl;

    angle_radius = Angle_two_vectors(x_sphere, -y_sphere, 0, inter.x, inter.y, 0);

    //********************************************************************************

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Очистка буфера цвета и глубины
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //cout << flag_cross << endl;

        
        if ((inter.flag_inter == true) && (R_turn != 0))
        {
            // Сохранение матрицы вида в стек
            glPushMatrix();
            // Функция управления камерой
            Move_camera(); 
            // Отрисовка осей
            Axe();
            // Отрисовка направляющих стрелок на осях
            Cursors();
            // Рисование полусферы
            Draw_sphere(x_sphere, -y_sphere, radius_sphere);
            // Отрисовка плоскости
            Show_plane();
            // Отображение траектории ЛА
            Aircraft_traectory(H, inter.x, inter.y, inter.z);
            bf_x = inter.x;
            bf_y = inter.y;
            bf_z = inter.z;
            inter = Intersection_sphere(H + R_turn / sin((90-pitch) * M_PI / 180), V, pitch, yaw, x_sphere, y_sphere, cos(angle_radius * M_PI / 180) * (radius_sphere + R_turn));
            turn.x = inter.x;
            turn.y = inter.y;
            turn.z = inter.z;
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
            // Сохранение матрицы вида в стек
            glPushMatrix();
            // Функция управления камерой
            Move_camera();
            // Отрисовка осей
            Axe();
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
            // Возвращение матрицы из стека
            glPopMatrix();
        }

        // Смена буфера
        glfwSwapBuffers(window);

        // Отключение событий
        glfwPollEvents();
    }

    // Очистка буфера
    glfwTerminate();
    return 0;
}