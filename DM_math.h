#ifndef DM_MATH_LIB_H
#define DM_MATH_LIB_H

// Объявление заголовочного файла dm_math_lib.h, предотвращающее множественное включение.

// Общие переменные, вынесенные за функции
const double pi = 3.14159265358979323846; // Константа pi
const double e = 2.718281828459045235;     // Константа e (число Эйлера)
double eps = 1e-12;                        // Точность вычислений

// Функция для вычисления факториала числа.
unsigned long int dmFactorial(int n) {
    return (n == 0 || n == 1) ? 1 : n * dmFactorial(n - 1); // Рекурсивное вычисление факториала
}

// Функция для вычисления абсолютного значения числа.
double dmAbs(double x) {
    return (x < 0) ? -x : x; // Возвращает модуль числа
}

// Функция для возведения числа в степень.
double dmPow(double base, int exponent) {
    double result = 1.0; // Инициализация результата
    for (int i = 0; i < exponent; ++i) {
        result *= base; // Умножение базы на себя exponent раз
    }
    return result;
}

// Функция для вычисления остатка от деления (модуля)
double dmMod(double x, double y) {
    return x - y * int(x / y); // Возвращает остаток от деления x на y
}

// Функция для вычисления синуса угла в радианах.
double dmSin(double x)
{
    int sign = (x < 0) ? -1 : 1; // Определение знака угла
    x = dmMod(dmAbs(x), 2 * pi); // Приведение угла к интервалу [0, 2*pi)
    if (x > pi) { x -= pi; sign *= -1; } // Приведение угла к интервалу [-pi, pi)
    if (x > pi / 2) x = pi - x; // Приведение угла к интервалу [-pi/2, pi/2)

    double t = x, s = x; // Инициализация переменных для ряда Тейлора
    for (int n = 3; dmAbs(t) > eps; n += 2) // Итерации по ряду Тейлора
        s += t = -t * x * x / n / (n - 1);
    return s * sign; // Возвращает синус угла
}

// Функция для вычисления косинуса угла в радианах.
double dmCos(double x)
{
    x = dmMod(dmAbs(x), 2 * pi); // Приведение угла к интервалу [0, 2*pi)

    double s = 1, t = 1;
    for (int n = 0; dmAbs(t) > eps; n++)
    {
        s += t = -(t * x * x) / ((2 * n + 2) * (2 * n + 1));
    }
    return s;
}

// Функция для вычисления натурального логарифма.
double dmLn(double x) {
    // Проверка на недопустимые значения
    if (x <= 0) {
        return 0;  // NaN
    }
    
    // Приведение x к разумному диапазону
    int power_adjust = 0;
    while (x > 1.0) {
        x /= e;
        power_adjust++;
    }
    while (x < .25) {
        x *= e;
        power_adjust--;
    }
    
    // Вычисление натурального логарифма с помощью ряда Тейлора
    x -= 1.0;
    double t = 0.0, s = 1.0, z = x;
    for (int k=1; k<=20; k++) {
        t += z * s / k;
        z *= x;
        s = -s;
    }
    
    // Комбинирование результата с power_adjust и возврат
    return t + power_adjust;
}

// Функция для вычисления логарифма с заданным основанием.
double dmLog(double x, double base) {
    if (base <= 0 || x <= 0) {
        return 0.0; // Логарифм не определен для x <= 0 или base <= 0
    }

    double result = dmLn(x) / dmLn(base); // Вычисление логарифма с помощью формулы замены основания
    return result;
}

// Функция для вычисления квадратного корня числа.
double dmSqrt(double x) {
    if (x < 0) {
        return 0.0; // Квадратный корень не определен для отрицательных чисел
    }

    double guess = x; // Начальное предположение
    double newGuess;
    int maxIterations = 1000; // Максимальное количество итераций

    while (maxIterations--) {
        newGuess = 0.5 * (guess + x / guess); // Улучшение предположения по методу Ньютона
        if (dmAbs(newGuess - guess) < eps) {
            return newGuess; // Возвращение при достижении необходимой точности
        }
        guess = newGuess; // Обновление предположения
    }

    return guess; // Возвращение последнего предположения после превышения максимального числа итераций
}

#endif // DM_MATH_LIB_H
