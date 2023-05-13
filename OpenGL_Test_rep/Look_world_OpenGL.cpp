// Подключение заголовочного файла
#include "Function_OpenGL.h"

/***********************************************************************************
 * @brief Создание стрелок для осей координат
 * @return Ничего
***********************************************************************************/
void Cursors()
{
    // Настройка координат пирамид
    float pyramid_x[] = { 13, 0, 0, 12, 0.5, -0.5, 12, -0.5, -0.5, 12, -0.5, 0.5, 12, 0.5, 0.5, 12, 0.5, -0.5 };
    float pyramid_y[] = { 0, 0, 13, -0.5, 0.5, 12, -0.5, -0.5, 12, 0.5, -0.5, 12, 0.5, 0.5, 12, -0.5, 0.5, 12 };
    float pyramid_z[] = { 0, -13, 0, 0.5, -12, -0.5, -0.5, -12, -0.5, -0.5, -12, 0.5, 0.5, -12, 0.5, 0.5, -12, -0.5 };

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
void Aircraft_traectory(float H, float x_end, float y_end, float z_end)
{
    // Настройка вершин
    float vert_x[] = { 0,0,H, x_end, y_end, z_end };

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