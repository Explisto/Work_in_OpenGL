// ����������� ������������� �����
#include "Function_OpenGL.h"

/***********************************************************************************
 * @brief �������� ������� ��� ���� ���������
 * @return ������
***********************************************************************************/
void Cursors()
{
    // ��������� ��������� �������
    float pyramid_x[] = { 13, 0, 0, 12, 0.5, -0.5, 12, -0.5, -0.5, 12, -0.5, 0.5, 12, 0.5, 0.5, 12, 0.5, -0.5 };
    float pyramid_y[] = { 0, 0, 13, -0.5, 0.5, 12, -0.5, -0.5, 12, 0.5, -0.5, 12, 0.5, 0.5, 12, -0.5, 0.5, 12 };
    float pyramid_z[] = { 0, -13, 0, 0.5, -12, -0.5, -0.5, -12, -0.5, -0.5, -12, 0.5, 0.5, -12, 0.5, 0.5, -12, -0.5 };

    // �����, ��� ����� ����������� ������ ������
    glEnableClientState(GL_VERTEX_ARRAY);
    // ���������� ������ �� ������� ������ ��� ������ �������
    glVertexPointer(3, GL_FLOAT, 0, &pyramid_x);
    // ��������� ����� ���������
    glColor3f(0.5f, 0.5f, 0.1f);
    // �������� ��������� � ���� ������������
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    // ����� - ���������� ��� ��������� ���� ����
    //*****************************************************
    glVertexPointer(3, GL_FLOAT, 0, &pyramid_y);
    glColor3f(0.5f, 0.5f, 0.1f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    glVertexPointer(3, GL_FLOAT, 0, &pyramid_z);
    glColor3f(0.5f, 0.5f, 0.1f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    //*****************************************************

    // ����� �� ���������� ������������� ������� ������
    glDisableClientState(GL_VERTEX_ARRAY);
}

/***********************************************************************************
 * @brief �������� ��������� ����� �������� ��
 * @return ������
***********************************************************************************/
void Point_sphere(float x, float y, float z, int code_sphere)
{
    // ���������� ������� ������� � ����
    glPushMatrix();
    // ����������� � �������� �����
    glTranslatef(x, y, z);
    Draw_sphere_traectory(0.0, 0.0, 0.2, code_sphere);
    // ����������� ������� �� �����
    glPopMatrix();
}
/***********************************************************************************
 * @brief �������� ��������� � ����� ��� ���
 * @param x_sp ���������� ������ ����� �� ��� oX
 * @param y_sp ���������� ������ ����� �� ��� oY
 * @param r ������ �����
 * @return ������
***********************************************************************************/
void Draw_sphere(float x_sp, float y_sp, float r)
{

    float di = 0.02;
    float dj = 0.04;
    float db = di * 2 * GLOBAL_PI;
    float da = dj * GLOBAL_PI;
    float p_1 = 0.0, p_2 = 0.0, p_3 = 0.0, p_4 = 0.0;

    // �������������� ���������
    for (float i = 0.0; i < 1.0; i += di)
    {
        // ������������ ���������
        for (float j = 0.5; j < 1.0; j += dj)
        {
            float b = i * 2 * GLOBAL_PI;
            float a = (j - 0.5) * GLOBAL_PI;

            glColor3f(1.0f, 1.0f, 0.0f);
            // ������������ ��������� �������
            glNormal3f(
                x_sp + cos(a + da / 2) * cos(b + db / 2),
                y_sp + cos(a + da / 2) * sin(b + db / 2),
                sin(a + da / 2));

            // �������� ���������������� ��� ���������
            glBegin(GL_QUADS);

            // ���������� ��������� ����� P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                y_sp + r * cos(a) * sin(b),
                r * sin(a));
            // ���������� ��������� ����� P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                y_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            // ���������� ��������� ����� P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                y_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            // ���������� ��������� ����� P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                y_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();

            // �������� �����
            glBegin(GL_LINE_STRIP);

            glColor3f(1.0f, 0.0f, 0.0f);
            // ��� ����� P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                y_sp + r * cos(a) * sin(b),
                r * sin(a));
            // ��� ����� P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                y_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            // ��� ����� P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                y_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            // ��� ����� P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                y_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();
        }
    }
}

/***********************************************************************************
 * @brief �������� ����� �� ���������� ��
 * @param x_sp ���������� ������ ����� �� ��� oX
 * @param y_sp ���������� ������ ����� �� ��� oY
 * @param r ������ �����
 * @return ������
***********************************************************************************/
void Draw_sphere_traectory(float x_sp, float y_sp, float r, int code_sphere)
{
    float di = 0.02;
    float dj = 0.04;
    float db = di * 2 * GLOBAL_PI;
    float da = dj * GLOBAL_PI;
    float p_1 = 0.0, p_2 = 0.0, p_3 = 0.0, p_4 = 0.0;

    // ����� - ������ ���������� ��
    if (code_sphere == 0)
    {
        glColor3f(1.0, 0.0, 0.0);
    }
    // ����� - ����� ���������� ��
    if (code_sphere == 1)
    {
        glColor3f(1.0, 0.0, 1.0);
    }
    // ����� - ����������� � ���������� - 1 �����
    if (code_sphere == 2)
    {
        glColor3f(0.0, 1.0, 0.0);
        r = 0.05;
    }
    // ����� - ����������� � ���������� - 2 ����� (���������)
    if (code_sphere == 3)
    {
        glColor3f(1.0, 0.0, 1.0);
    }
    // ����� - ����� ���������
    if (code_sphere == 4)
    {
        glColor3f(1.0, 0.0, 1.0);
        r = 0.1;
    }
    // ����� - ������� ����� ��
    if (code_sphere == 5)
    {
        r = 0.1;
        glColor3f(1.0, 0.5, 0.5);
    }
    // ����� - ����� ����� ��������� � ����������
    if (code_sphere == 6)
    {
        r = 0.1;
        glColor3f(0.3, 0.2, 0.8);
    }
    // ����� - �������� ����� ���������� �� �� ����������
    if (code_sphere == 7)
    {
        r = 0.1;
        glColor3f(0.5, 0.5, 0.5);
    }

    // �������������� ���������
    for (float i = 0.0; i < 1.0; i += di)
    {
        // ������������ ���������
        for (float j = 0.0; j < 1.0; j += dj)
        {
            float b = i * 2 * GLOBAL_PI;
            float a = (j - 0.5) * GLOBAL_PI;

            // ������������ ��������� �������
            glNormal3f(
                x_sp + cos(a + da / 2) * cos(b + db / 2),
                y_sp + cos(a + da / 2) * sin(b + db / 2),
                sin(a + da / 2));

            // �������� ���������������� ��� ���������
            glBegin(GL_QUADS);

            // ���������� ��������� ����� P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                y_sp + r * cos(a) * sin(b),
                r * sin(a));
            // ���������� ��������� ����� P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                y_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            // ���������� ��������� ����� P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                y_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            // ���������� ��������� ����� P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                y_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();

        }
    }
}

/**********************************************************************************
* @brief ��������� ���������, �� ������� ��������� ���������
* @return ������
**********************************************************************************/
void Show_plane()
{
    // ������������� ��������� ��������� - ���� �����
    float vert_line_1[] = { 0,0,0, 0,-11,0 };
    float vert_line_2[] = { 0,0,0, 11,0,0 };

    // �����, ��� ����� ����������� ������ ������
    glEnableClientState(GL_VERTEX_ARRAY);
    // ���������� ������ �� ������� ������
    glVertexPointer(3, GL_FLOAT, 0, &vert_line_1);

    // ���� �������� ����� �����
    for (int count_line_1 = 0; count_line_1 < 12; count_line_1++)
    {
        // ���������� ������� ������� � ����
        glPushMatrix();
        // ��������� ����� ���������
        glColor3f(0, 1, 0);
        // ������� ��������� �����
        glTranslatef(count_line_1, 0, 0);
        // �������� ��������� � ���� �����
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        // ����������� ������� �� �����
        glPopMatrix();
    }

    // �����, ��� ������ ������ ������ �� ����� ��������������
    glDisableClientState(GL_VERTEX_ARRAY);

    // �����, ��� ����� ����������� ������ ������
    glEnableClientState(GL_VERTEX_ARRAY);
    // ���������� ������ �� ������� ������
    glVertexPointer(3, GL_FLOAT, 0, &vert_line_2);

    for (int count_line_2 = 0; count_line_2 < 12; count_line_2++)
    {
        // ���������� ������� ������� � ����
        glPushMatrix();
        // ��������� ����� ���������
        glColor3f(1, 0.8, 0);
        // ������� ��������� �����
        glTranslatef(0, -count_line_2, 0);
        // �������� ��������� � ���� �����
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        // ����������� ������� �� �����
        glPopMatrix();
    }
    // �����, ��� ������ ������ ������ �� ����� ��������������
    glDisableClientState(GL_VERTEX_ARRAY);
}

/***********************************************************************************
 * @brief �������� ���� ������� ���������
 * @return ������
***********************************************************************************/
void Axe()
{
    // ������� �����, ��������������� ��� ��
    float vert_x[] = { 0,0,0, 12,0,0 };
    float vert_y[] = { 0,0,0, 0,-12,0 };
    float vert_z[] = { 0,0,0, 0,0,12 };

    // ������ �����
    glLineWidth(10);

    // �����, ��� ����� ����������� ������ ������
    glEnableClientState(GL_VERTEX_ARRAY);
    // ���������� ������ �� ������� ������
    glVertexPointer(3, GL_FLOAT, 0, &vert_x);

    // ���������� ������� ������� � ����
    glPushMatrix();
    // ��������� ����� ���������
    glColor3f(0, 0, 1);
    // �������� ��������� � ���� �����
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    // ����������� ������� �� �����
    glPopMatrix();

    // ����� - ���������� ��� ��������� ���� ����
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

    // ������ �����
    glLineWidth(1);
}

/***********************************************************************************
 * @brief �������� ���������� ������ ��
 * @return ������
***********************************************************************************/
void Aircraft_traectory(float H, float x_end, float y_end, float z_end)
{
    // ��������� ������
    float vert_x[] = { 0, 0, H, x_end, y_end, z_end };

    // ������ �����
    glLineWidth(10);

    // �����, ��� ����� ����������� ������ ������
    glEnableClientState(GL_VERTEX_ARRAY);
    // ���������� ������ �� ������� ������
    glVertexPointer(3, GL_FLOAT, 0, &vert_x);

    // ���������� ������� ������� � ����
    glPushMatrix();
    // ��������� ����� ���������
    glColor3f(0, 0.8, 0);
    // �������� ��������� � ���� �����
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    // ����������� ������� �� �����
    glPopMatrix();

}