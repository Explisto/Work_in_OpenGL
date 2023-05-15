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
void Aircraft_turn(float H, float V, float pitch, float yaw, float radius, float R_turn)
{

    // Массив точек: первая - на расстоянии радиуса виража от начальной точки, вторая - центр окружности виража ЛА
    float vert_1[] = { 0, 0, H + R_turn / sin((90 - pitch) * M_PI / 180), inter.x, inter.y, inter.z + R_turn / sin((90 - pitch) * M_PI / 180) };

    // Точки для построения окружности
    float x_rotate, y_rotate, z_rotate = 0;

    // Угол поворота точки на окружности
    float alfa = 0;

    // Счетчик окружности для отрисовки
    float circle_def = R_turn * 25;

    // Установка размера точки - начала ухода ЛА

    // Установка размера точки - точка пересечения сфер
    glPointSize(20);
    glBegin(GL_POINTS);

    // Установка цвета примитива
    glColor3d(0.8, 0.2, 0.5);
    // Координаты точки контакта сфер
    //glVertex3d(contact.x, contact.y, contact.z);

    glEnd();

    // Установка размера точки - точка центра окружности ухода ЛА
    glPointSize(20);
    glBegin(GL_POINTS);

    // Установка цвета примитива
    glColor3d(1, 0.8, 0);
    // Координаты центра окружности ухода ЛА
    //glVertex3d(turn.x, turn.y, turn.z);

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
        if ((count_sphere >= 20) && (count_sphere % 10 == 0))
        {
            Draw_sphere_traectory(x_rotate, y_rotate, 0.05); // Вызов функции построения сферы
        }
        if (count_sphere == (int(circle_def) - 2))
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
    setlocale(LC_ALL, "Russian");
    //SetConsoleCP(1251);
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

    float cos_roll; // Значение косинуса угла крена

    bool flag_all;

    // Коэффициенты масштабирования окна
    float coefficient_scale_big = 1000;
    float coefficient_scale_small = 100;

    // угол между векторами траектории и центра полусферы
    float angle_radius;

    // Указатель на созданный экземпляр окна
    GLFWwindow* window;
    
    // Размер выходного окна glfw
    int width = 1000;
    int height = 1000;

    // Коэффициент масштаба экрана
    float ratio = width / height;

    // Переменная метка нажатия клавиши смены значений
    bool flag_console = true;

    // Переменная - файловый буфер
    string file_buffer;
    // Название файла, из которого берутся значения
    string name_file = "Test_case.txt";

    // Создание экземпляра объекта для чтения из файла
    ifstream fin;
    // Открытие файла
    fin.open(name_file);

    if (!fin.is_open())
    {
        cout << "Ошибка при открытии файла!" << endl;
        exit(0);
    }
    // Проверка инициализации библиотеки GLFW
    if (!glfwInit())
        return -1;

    // Создание сового окна с заданными размерами
    window = glfwCreateWindow(width, height, "Aircraft", NULL, NULL);
    // Если окно не создано
    if (!window)
    {
        glfwTerminate(); // Уничтожение окна
        return -1;
    }
    //glfwMaximizeWindow(window);
    // Создание контекста окна
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW is not\n";
        return -1;
    }

    glFrustum(-1, 1, -1, 1, 1,80);

    cout << "===================================================" << endl;
    cout << "!Уход ЛА по круговой траектории!" << endl;
    cout << "===================================================" << endl;

    ///****************************************************************
    // Математические расчеты пересечения заданной траектории и сферы
    ///************************************************************

    // Основной цикл программы, пока не закрыто окно glfw
    while (!glfwWindowShouldClose(window))
    {
        if (GetKeyState(VK_SPACE) < 0)
        {
            flag_console = true;
            Sleep(250);
        }
        if (flag_console == true)
        {
            getline(fin, file_buffer);
            cout << file_buffer << endl;
            if (fin.eof())
            {
                fin.clear();
                fin.seekg(0);
                getline(fin, file_buffer);
            }
            getline(fin, file_buffer);
            H = stof(file_buffer);
            cout << H << " = H" << endl;
            getline(fin, file_buffer);
            V = stof(file_buffer);
            cout << V << " = V" << endl;
            getline(fin, file_buffer);
            pitch = stof(file_buffer);
            getline(fin, file_buffer);
            yaw = stof(file_buffer);
            getline(fin, file_buffer);
            x_sphere = stof(file_buffer);
            getline(fin, file_buffer);
            y_sphere = stof(file_buffer);
            getline(fin, file_buffer);
            radius_sphere = stof(file_buffer);
            //
            H = H / coefficient_scale_big;
            V = V / coefficient_scale_small;
            x_sphere = x_sphere / coefficient_scale_big;
            y_sphere = y_sphere / coefficient_scale_big;
            radius_sphere = radius_sphere / coefficient_scale_big;
            //
            inter = Intersection_sphere(H, V, pitch, yaw, x_sphere, y_sphere, radius_sphere);

            flag_all = inter.flag_inter;

            cos_roll = atanf(tanf(yaw * M_PI / 180) / cosf(pitch * M_PI / 180));

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
            }

            R_turn = (pow(V, 2)) / (GLOBAL_EARTH_ACSELERATION * sqrt(pow(n_y, 2) - 1));

            cout << "Радиус виража = " << R_turn << " метров;" << endl;

            angle_radius = Angle_two_vectors(x_sphere, -y_sphere, 0, inter.x, inter.y, 0);

            //********************************************************************************

            if (inter.flag_inter == true)
            {
                bf_x = inter.x;
                bf_y = inter.y;
                bf_z = inter.z;
                inter = Intersection_sphere(H + R_turn / sin((90 - pitch) * M_PI / 180), V, pitch, yaw, x_sphere, y_sphere, cos(angle_radius * M_PI / 180) * (radius_sphere + R_turn));
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
                Draw_sphere(track.x, track.y, 2);
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
        // Очистка буфера цвета и глубин
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ///////////////////////////////////////////////////////////////////////////////
        // Изменение размера окна

        // Отслеживание изменения окна
        glfwGetWindowSize(window, &width, &height);
        //
        glViewport(0, 0, width, height);
        //
        glScissor(0, 0, width, height);
        //
        //glFrustum(3, 3, 3, 3, 2, 80);
        //
        /////////////////////////////////////////////////////////////////////////////

        if ((flag_all == true) && (R_turn != 0))
        {
            // Сохранение матрицы вида в стек
            glPushMatrix();
            // Функция управления камерой
            Move_camera(flag_console);
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
            // Отрисовка полуокружности ухода ЛА
            Aircraft_turn(H, V, pitch, yaw, radius_sphere, R_turn);
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

        // Окончание обработки новых значений
        flag_console = false;

        // Смена буфера
        glfwSwapBuffers(window);

        // Отслеживание событий внутри окна
        glfwPollEvents();
    }

    // Уничтожение окна
    glfwTerminate();
    return 0;
}