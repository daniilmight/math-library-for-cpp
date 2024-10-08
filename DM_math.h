#ifndef DM_MATH_LIB_H
#define DM_MATH_LIB_H

const double pi = 3.14159265358979323846; /* Константа pi */
const double e = 2.718281828459045235; /* Константа e (число Эйлера) */
const double eps = 1e-15; /* Точность вычислений */

double dmAbs(double x) { /* Метод: Условная проверка */
    return (x < 0) ? -x : x; /* Возвращает модуль числа */
}

double dmMod(double x, double y) { /* Метод: Целочисленное деление и вычитание */
    return x - y * int(x / y); /* Возвращает остаток от деления x на y */
}

double dmSin(double x) { /* Метод: Ряд Тейлора */
    x = dmMod(x, 2 * pi); /* Приводим значение угла к интервалу [0, 2*pi) */
    double sum = x, term = x; /* Инициализация переменных для ряда Тейлора */
    for (int n = 3; dmAbs(term) > eps; n += 2) { /* Итеративно вычисляем члены ряда Тейлора для синуса */
        term *= -x * x / (n * (n - 1)); /* Обновляем текущий член ряда */
        sum += term; /* Обновляем сумму ряда */
    }
    return sum; /* Возвращаем сумму ряда */
}

double dmCos(double x) { /* Метод: Ряд Тейлора */
    x = dmMod(x, 2 * pi); /* Приводим значение угла к интервалу [0, 2*pi) */
    double sum = 1, term = 1; /* Инициализация переменных для ряда Тейлора */
    for (int n = 2; dmAbs(term) > eps; n += 2) { /* Итеративно вычисляем члены ряда Тейлора для косинуса */
        term *= -x * x / (n * (n - 1)); /* Обновляем текущий член ряда */
        sum += term; /* Обновляем сумму ряда */
    }
    return sum; /* Возвращаем сумму ряда */
}

double dmLn(double x) { /* Метод: Ряд Тейлора и масштабирование */
    if (x <= 0) return 0; /* Проверка на недопустимые значения */
    int power_adjust = 0; /* Инициализация счетчика сдвига степени */
    while (x > 1.0) { /* Приведение значения x к диапазону [0.25, 1.0] */
        x /= e; /* Делим x на e */
        power_adjust++; /* Увеличиваем power_adjust */
    }
    while (x < 0.5) { /* Приведение значения x к диапазону [0.25, 1.0] */
        x *= e; /* Умножаем x на e */
        power_adjust--; /* Уменьшаем power_adjust */
    }
    x -= 1.0; /* Вычитаем 1 из x */
    double sum = 0.0, term = x; /* Инициализация переменных для ряда Тейлора */
    for (int k = 1; dmAbs(term) > eps; k++) { /* Итеративно вычисляем члены ряда Тейлора */
        sum += term / k; /* Обновляем сумму ряда */
        term *= -x; /* Обновляем текущий член ряда */
    }
    return sum + power_adjust; /* Возвращаем результат с учетом сдвига степени */
}

double dmExp(double x) { /* Метод: Ряд Тейлора */
    double sum = 1.0; /* Инициализация суммы ряда */
    double term = 1.0; /* Инициализация текущего члена ряда */
    for (int n = 1; dmAbs(term) > eps; ++n) { /* Итеративно вычисляем члены ряда Тейлора */
        term *= x / n; /* Обновляем текущий член ряда */
        sum += term; /* Обновляем сумму ряда */
    }
    return sum; /* Возвращаем сумму ряда */
}

double dmPow(double base, double exponent) { /* Метод: Экспонента и натуральный логарифм */
    if (base <= 0) return 0; /* Проверка на недопустимые значения */
    return dmExp(exponent * dmLn(base)); /* Вычисляем степень числа через экспоненту и логарифм */
}

double dmLog(double x, double base) { /* Метод: Формула замены основания */
    return (base <= 0 || x <= 0) ? 0.0 : dmLn(x) / dmLn(base); /* Логарифм не определен для x <= 0 или base <= 0 */
}

double dmSqrt(double x) { /* Метод: Метод Ньютона */
    if (x < 0) return 0.0; /* Проверка на недопустимые значения */
    double guess = x; /* Начальное предположение */
    double newGuess; /* Переменная для нового предположения */
    int maxIterations = 1000; /* Максимальное количество итераций */
    while (maxIterations--) { /* Итерационный процесс метода Ньютона */
        newGuess = 0.5 * (guess + x / guess); /* Улучшение предположения по методу Ньютона */
        if (dmAbs(newGuess - guess) < eps) return newGuess; /* Возвращение при достижении необходимой точности */
        guess = newGuess; /* Обновление предположения для следующей итерации */
    }
    return guess; /* Возвращение последнего предположения после превышения максимального числа итераций */
}

double dmTan(double x) { /* Метод: Отношение синуса к косинусу */
    return dmSin(x) / dmCos(x); /* Возвращаем тангенс угла */
}

double dmCot(double x) { /* Метод: Обратное значение тангенса */
    return 1.0 / dmTan(x); /* Возвращаем котангенс угла */
}

#endif /* DM_MATH_LIB_H */
