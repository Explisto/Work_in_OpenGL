// ����������� ������������� �����
#include "Function_OpenGL.h"

void Interface_low(float H, float V, float pitch, float yaw, float x_sphere, float y_sphere, float radius_sphere)
{
    cout << "������� ������ ��� ������ ���������:" << endl;
    cout << "��������� ������ ��:" << H << " ������;" << endl;
    cout << "�������� ��: " << V << " ��/�;" << endl;
    cout << "���� ������� ��: " << pitch << " ��������;" << endl;
    cout << "���� �������� ��: " << yaw << " ��������;" << endl;
    cout << "���������� ������ ��������� �� ��� oX: " << x_sphere << " ������;" << endl;
    cout << "���������� ������ ��������� �� ��� oY: " << y_sphere << " ������;" << endl;
    cout << "������ ���������: " << radius_sphere << " ������;" << endl;
    cout << "===================================================" << endl;
}