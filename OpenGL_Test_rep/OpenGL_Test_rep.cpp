// Main - файл
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
 * @return Ничего
***********************************************************************************/
void Aircraft_turn(float H, float V, float pitch, float yaw, float radius, float R_turn)
{
    // Точки для построения окружности
    float x_rotate, y_rotate, z_rotate = 0;

    // Угол поворота точки на окружности
    float alfa = 0;

    // Счетчик окружности для отрисовки
    float circle_def = 150;

    // Построение траектории ухода ЛА
    float count_circle;
    
    count_circle = Angle_two_vectors(turn.x, turn.y, 0, turn.x - track.x, turn.y - track.y, turn.z - track.z);

    count_circle = int(count_circle);
    
    glColor3f(0.1f, 1.0f, 0.2f);

    // Сохранение текущей матрицы в стек
    glPushMatrix();
    // Перемещение
    glTranslated(turn.x, turn.y, turn.z);
    // Поворот окружности относительно оси oX
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    // Поворот окружности на угол рысканья
    glRotatef(-yaw, 0.0f, 1.0f, 0.0f);
    // Отрисовка окружности
    glBegin(GL_LINE_STRIP);
    // Установка цвета траектории
    glColor3f(1.0, 0.0, 0.0);
    // Цикл - нахождение точек окружности
    for (count_circle; count_circle < int(circle_def); count_circle++)
    {
        // Нахождение угла поворота точки
        alfa = count_circle / 180.0f * GLOBAL_PI;
        // Нахождение координат точки окружности
        x_rotate = cos(alfa) * R_turn;
        y_rotate = sin(alfa) * R_turn;
        // Отображение точки
        glVertex3f(0, y_rotate, x_rotate);
    }
    // Закончили отрисовку
    glEnd();
    // Конечная точка траектории ЛА
    Point_sphere(0, y_rotate, x_rotate, 7);
    // Возвращение матрицы вида из стека
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

    float bf_x, bf_y, bf_z; // Буферные переменные

    bool flag_all; // Метка захода в цикл пересчета значений

    // Коэффициенты масштабирования окна
    float coefficient_scale_big = 1000.0;
    float coefficient_scale_small = 100.0;
    // Угол между векторами траектории и центра полусферы
    float angle_radius;

    // Указатель на созданный экземпляр окна
    GLFWwindow* window;

    // Размер выходного окна glfw
    int viewportWidth = 600;
    int viewportHeight = 600;

    // Установка буферных переменных для размера окна
    float buf_h = viewportHeight;
    float buf_w = viewportWidth;

    // Коэффициент масштаба экрана
    float ratio = viewportWidth / viewportHeight;

    // Переменная метка нажатия клавиши смены значений
    bool flag_console = true;

    // Проверка инициализации библиотеки GLFW
    if (!glfwInit())
        return -1;

    // Создание нового окна с заданными размерами
    window = glfwCreateWindow(viewportWidth, viewportHeight, "Aircraft", NULL, NULL);

    // Если окно не создано
    if (!window)
    {
        glfwTerminate(); // Уничтожение окна
        return -1;
    }
    // Разворот окна на весь экран
    glfwMaximizeWindow(window);
    // Создание контекста окна
    glfwMakeContextCurrent(window);

    // Проверка инициализации библиотеки GLEW
    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW is not!" << endl;
        return -1;
    }
    // Установка дальности прорисовки сцены
    glFrustum(-1, 1, -1, 1, 1, 50);

    // Основной цикл программы, пока не закрыто окно glfw
    while (!glfwWindowShouldClose(window))
    {
        // pitch = pitch - 1;
        // Отслеживание изменения размера окна
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

        // Отслеживание изменения размера окна
        if ((buf_w != viewportWidth) || buf_h != viewportHeight)
        {
            // Изменение окна OpenGL
            glViewport(0, 0, viewportWidth, viewportHeight);
            // Коэффициент масштабирования
            ratio = (float)viewportWidth / (float)viewportHeight;
            // Изменение матрицы проекции
            glOrtho(ratio, ratio, 2, 2, 2, 80);
            // Установка новых значений
            buf_w = viewportWidth;
            buf_h = viewportHeight;
        }
        glViewport(0, 0, viewportWidth, viewportHeight);
        // Окончание работы программы при помощи нажатия клавиши Escape
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        // Блок - отслеживание действий пользователя при изменении входных параметров
        // Изменение знака изменения
        if (GetKeyState(VK_NUMPAD0) < 0)
        {
            // Изменение знака
            sign_delta = -sign_delta;
            Sleep(250);
        }
        // Изменение значения начальной высоты
        if (GetKeyState(VK_NUMPAD1) < 0)
        {
            flag_console = true;
            // Изменение значения
            H_input = H_input + (H_delta * sign_delta);
            // Проверки на введенные значения
            if (H_input < 1000)
            {
                H_input = 1000;
            }
            if (H_input > 12000)
            {
                H_input = 12000;
            }
            // Бездействие от залипания клавиш
            Sleep(50);
        }
        // Далее - аналогично
        if (GetKeyState(VK_NUMPAD2) < 0)
        {
            flag_console = true;
            V_input = V_input + (V_delta * sign_delta);
            if (V_input < 400)
            {
                V_input = 400;
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
            // Проверки, чтобы полусфера не вышла за пределы отведенной плоскости
            if (Check_input_data((X_input + (X_delta * sign_delta)) / coefficient_scale_big, Y_input / coefficient_scale_big, Radius_input / coefficient_scale_big))
            {
                X_input = X_input + (X_delta * sign_delta);
            }
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD6) < 0)
        {
            flag_console = true;
            // Проверки, чтобы полусфера не вышла за пределы отведенной плоскости
            if (Check_input_data(X_input / coefficient_scale_big, (Y_input + (Y_delta * sign_delta)) / coefficient_scale_big, Radius_input / coefficient_scale_big))
            {
                Y_input = Y_input + (Y_delta * sign_delta);
            }
            Sleep(50);
        }
        if (GetKeyState(VK_NUMPAD7) < 0)
        {
            flag_console = true;
            // Проверки, чтобы полусфера не вышла за пределы отведенной плоскости
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
        // Если произошло изменение входных параметров
        if (flag_console == true)
        {
            cout << "=========================================================" << endl;
            cout << "H = " << H_input << endl;
            cout << "V = " << V_input << endl;
            cout << "Pitch = " << pitch << endl;
            cout << "Yaw = " << yaw << endl;
            cout << "X = " << X_input << endl;
            cout << "Y = " << Y_input << endl;
            cout << "R = " << Radius_input << endl;
            // Пересчет значений с учетом коэффициентов
            H = H_input / coefficient_scale_big;
            V = V_input / coefficient_scale_small;
            x_sphere = X_input / coefficient_scale_big;
            y_sphere = Y_input / coefficient_scale_big;
            radius_sphere = Radius_input / coefficient_scale_big;
            // Нахождение точек пересечения траектории и полусферы
            inter = Intersection_sphere(H, V, pitch, yaw, x_sphere, y_sphere, radius_sphere);
            // Если происходит пересечение за плоскостью, то отбрасываем его
            if (inter.z < 0)
            {
                inter.flag_inter = false;
            }
            // Установка флага пересечения
            flag_all = inter.flag_inter;
            // Нахождение радиуса виража
            R_turn = Search_R_turn(H, V, pitch, yaw);
            // Находим угол между векторами радиуса и траектории
            angle_radius = Angle_two_vectors(x_sphere, -y_sphere, 0, inter.x, inter.y, 0);
            //********************************************************************************
            // Если есть пересечение луча со сферой
            if (inter.flag_inter == true)
            {
                // Создание буферных переменных
                bf_x = inter.x;
                bf_y = inter.y;
                bf_z = inter.z;
                // Нахождение точки центра окружности
                turn = Angle_turn(x_sphere, y_sphere, radius_sphere, pitch, yaw, R_turn, V, inter.x, inter.y, inter.z, H);
                turn.flag_turn = inter.flag_inter;
                // Нахождение координат точки начала увода ЛА
                track = Track_aircraft(turn.x, turn.y, turn.z, H, V, pitch, yaw);
                // Нахождение точки контакта сферы и окружности
                angle_radius = Angle_two_vectors(x_sphere, -y_sphere, 0, turn.x, turn.y, 0);
                contact = Contact_turn(x_sphere, y_sphere, radius_sphere, pitch, yaw, R_turn, V, inter.x, inter.y, inter.z, H);
                // Возвращение значений
                inter.x = bf_x;
                inter.y = bf_y;
                inter.z = bf_z;
            }
            //********************************************************************************
        }
        // Установка цвета фона
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Очистка буфера цвета и глубин
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Если есть пересечение сферы и луча
        if ((flag_all == true) && (R_turn != 0))
        {
            // Сохранение матрицы вида в стек
            glPushMatrix();
            // Функция управления камерой
            Move_camera();
            // Отрисовка осей
            Axe();
            // Сфера - начала траектории ЛА
            Point_sphere(0, 0, H, 0);
            // Отрисовка направляющих стрелок на осях
            Cursors();
            // Сфера - пересечение траектории и сферы
            Point_sphere(turn.x, turn.y, turn.z, 2);
            // Точка касания окружности и сферы
            Point_sphere(contact.x, contact.y, contact.z, 6);
            // Рисование полусферы
            Draw_sphere(x_sphere, -y_sphere, radius_sphere);
            // Отрисовка плоскости
            Show_plane();
            // Точка пересечения со сферой
            Point_sphere(bf_x, bf_y, bf_z, 2);
            // Point_sphere_test(turn.x, turn.y, turn.z, 8, R_turn);

            // Нахождение координат конечной точки движения ЛА
            inter = Not_intersection(pitch, yaw, H, V);
            if ((x_inter_2 != 0) && (y_inter_2 != 0) && (z_inter_2 != 0) && (z_inter_2 >= 0))
            {
                // Построение конечной точки ЛА
                Point_sphere(x_inter_2, y_inter_2, z_inter_2, 3);
            }
            // Построение второй точки пересечения сферы и ЛА
            Point_sphere(inter.x, inter.y, inter.z, 1);
            // Построение конечной точки ЛА
            Point_sphere(track.x, track.y, track.z, 5);
            // Построение центра полусферы
            Point_sphere(x_sphere, -y_sphere, 0, 4);
            // Отображение траектории ЛА
            Aircraft_traectory(H, inter.x, inter.y, inter.z);
            // Включение отрисовки
            glEnable(GL_DEPTH_TEST);
            // Построение конечной точки ЛА
            Point_sphere(track.x, track.y, track.z, 5);
            //glDisable(GL_DEPTH_TEST);
            // Условие, если пересечение траектории со сферой происходит за основной плоскостью
            if (bf_z >= 0)
            {
                // Отрисовка полуокружности ухода ЛА
                Aircraft_turn(H, V, pitch, yaw, radius_sphere, R_turn);
            }
            else
            {
                // Отрисовка конечной точки траектории ЛА
                Point_sphere(inter.x, inter.y, inter.z, 3);
            }
            // Возвращение матрицы из стека
            glPopMatrix();
        }
        // Если нет пересечения луча и сферы
        else
        {
            // Сохранение матрицы вида в стек
            glPushMatrix();
            // Функция управления камерой
            Move_camera();
            // Отрисовка осей
            Axe();
            // Сфера начала траектории ЛА
            Point_sphere(0, 0, H, 0);
            // Построение центра полусферы
            Point_sphere(x_sphere, -y_sphere, 0, 4);
            // Отрисовка направляющих стрелок на осях
            Cursors();
            // Рисование полусферы
            Draw_sphere(x_sphere, -y_sphere, radius_sphere);
            // Отрисовка плоскости
            Show_plane();
            // Нахождение координат конечной точки движения ЛА
            inter = Not_intersection(pitch, yaw, H, V);
            // Построение конечной точки ЛА
            Point_sphere(inter.x, inter.y, inter.z, 1);
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
    // Окончание программы
    return 0;
}