#include <iostream>
#include "DM_math.h"
#include <locale>

int main() {
    setlocale(LC_ALL, "Russian");
    float angleInRadians;
    std::cout << "Введите угол в радианах: ";
    std::cin >> angleInRadians;

    // Вычисление и вывод синуса и косинуса.
    std::cout << "Синус угла: " << dmSin(angleInRadians) << "\n";
    std::cout << "Косинус угла: " << dmCos(angleInRadians) << "\n";

    float number, base;
    std::cout << "Введите число для логарифма и основание: ";
    std::cin >> number;
    std::cin >> base;

    // Вычисление и вывод логарифма.
    std::cout << "Логарифм числа: " << dmLog(number, base) << "\n";

    // Вычисление и вывод квадратного корня.
    std::cout << "Квадратный корень числа: " << dmSqrt(number) << "\n";

    return 0;
}
