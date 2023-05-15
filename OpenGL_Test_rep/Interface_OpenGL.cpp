// Подключение заголовочного файла
#include "Function_OpenGL.h"

void Interface_low(float H, float V, float pitch, float yaw, float x_sphere, float y_sphere, float radius_sphere)
{
    cout << "Входные данные для работы программы:" << endl;
    cout << "Начальная высота ЛА:" << H << " метров;" << endl;
    cout << "Скорость ЛА: " << V << " км/ч;" << endl;
    cout << "Угол тангажа ЛА: " << pitch << " градусов;" << endl;
    cout << "Угол рысканья ЛА: " << yaw << " градусов;" << endl;
    cout << "Координаты центра полусферы по оси oX: " << x_sphere << " метров;" << endl;
    cout << "Координаты центра полусферы по оси oY: " << y_sphere << " метров;" << endl;
    cout << "Радиус полусферы: " << radius_sphere << " метров;" << endl;
    cout << "===================================================" << endl;
}