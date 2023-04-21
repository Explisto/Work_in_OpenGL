// OpenGL_Test_rep.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>



float theta = 0.0f;
float turn_x = 2;
float turn_z = 0;
POINTFLOAT pos = { 1,1 };

void Show_plane()
{
    float vert_line_1[] = { 1,1,0, 1,-12,0 };
    float vert_line_2[] = { 0,0,0, 11,0,0 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert_line_1);

    for (int i = 0; i < 10; i++)
    {
        glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(i, 0, 0);
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        glPopMatrix();
    }
    glDisableClientState(GL_VERTEX_ARRAY);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert_line_2);
    
    for (int j = 0; j < 12; j++)
    {
        glPushMatrix();
        glColor3f(1, 0.8, 0);
        glTranslatef(0, -j, 0);
        glDrawArrays(GL_LINE_STRIP, 0, 2);
        glPopMatrix();
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Axe()
{
    float vert_x[] = { 0,0,0, 12,0,0 };
    float vert_y[] = { 0,0,0, 0,-12,0 };
    float vert_z[] = { 0,0,0, 0,0,12 };

    glLineWidth(10);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert_x);
    
    glPushMatrix();
    glColor3f(0, 0, 1);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    glPopMatrix();

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

    glLineWidth(1);

}

void aircraft_path()
{
    float vert_x[] = { 0,0,5, 3,-3,-6 };

    glLineWidth(10);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert_x);

    glPushMatrix();
    glColor3f(1, 0.5, 0.5);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    glPopMatrix();

}

void cursors()
{
    float pyramid[] = { 12,0,2, 1,1,0, 1,-1,0, -1,-1,0, -1,1,0, 1,1,0};
    glEnable(GL_DEPTH_TEST);

    glVertexPointer(3, GL_FLOAT, 0, &pyramid);
    glColor3f(1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    glEnableClientState(GL_VERTEX_ARRAY);

}

void draw_sphere_(float r)
{

    float pi = 3.141592;
    float di = 0.02;
    float dj = 0.04;
    float db = di * 2 * pi;
    float da = dj * pi;
    float p_1, p_2, p_3, p_4;
    float x_sp, z_sp;

    x_sp = 3;
    z_sp = -3;


    for (float i = 0.0; i < 1.0; i += di) //horizonal
    {
        for (float j = 0.5; j < 1.0; j += dj) //vertical
        {
            float b = i * 2 * pi;      //0     to  2pi
            float a = (j - 0.5) * pi;  //-pi/2 to pi/2

            glColor3f(1.0f, 1.0f, 0.0f);
            //normal
            glNormal3f(
                x_sp + cos(a + da / 2) * cos(b + db / 2),
                z_sp + cos(a + da / 2) * sin(b + db / 2),
                sin(a + da / 2));

            glBegin(GL_QUADS);
            //P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                z_sp + r * cos(a) * sin(b),
                r * sin(a));
            //P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                z_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            //P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                z_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            //P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                z_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();

            
            glBegin(GL_LINE_STRIP);

            glColor3f(1.0f, 0.0f, 0.0f);
            //P1

            glVertex3f(
                x_sp + r * cos(a) * cos(b),
                z_sp + r * cos(a) * sin(b),
                r * sin(a));
            //P2

            glVertex3f(
                x_sp + r * cos(a) * cos(b + db),
                z_sp + r * cos(a) * sin(b + db),
                r * sin(a));
            //P3

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b + db),
                z_sp + r * cos(a + da) * sin(b + db),
                r * sin(a + da));
            //P4

            glVertex3f(
                x_sp + r * cos(a + da) * cos(b),
                z_sp + r * cos(a + da) * sin(b),
                r * sin(a + da));
            glEnd();
            
        }
    }
}


void Move_camera()
{
    if (GetKeyState(VK_UP) < 0)
    {
        turn_x += 0.1;
        if (turn_x > 180)
        {
            turn_x = 180;
        }
    }
    if (GetKeyState(VK_DOWN) < 0)
    {
        turn_x -= 0.1;
        if (turn_x < 0)
        {
            turn_x = 0;
        }
    }
    if (GetKeyState(VK_LEFT) < 0)
    {
        turn_z += 0.1;
    }
    if (GetKeyState(VK_RIGHT) < 0)
    {
        turn_z -= 0.1;
    }

    float angle = -turn_z / 180 * M_PI;
    float speed = 0;
    if (GetKeyState('W') < 0) speed = 0.01;
    if (GetKeyState('S') < 0) speed = -0.01;
    if (GetKeyState('A') < 0)
    {
        speed = -0.01;
        angle -= M_PI * 0.5;
    }
    if (GetKeyState('D') < 0)
    {
        speed = -0.01;
        angle += M_PI * 0.5;
    }
    if (speed != 0)
    {
        pos.x += sin(angle) * speed;
        pos.y += cos(angle) * speed;
    }
    glRotatef(-turn_x, 1,0,0);
    glRotatef(-turn_z, 0, 0, 1);
    glTranslatef(-pos.x, -pos.y, -3);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Aircraft", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW is not\n";
        return -1;
    }

    glFrustum(-1, 1, -1, 1, 2,80);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //
        glPushMatrix();
        Move_camera();
        Axe();
        cursors();
        draw_sphere_(1);
        Show_plane();
        aircraft_path();
        glPopMatrix();
        //
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
