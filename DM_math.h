#define DM_MATH_LIB_H

// Функция для вычисления факториала числа.
int factorial(int n) {
    return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
}

// Функция для вычисления абсолютного значения числа.
float dmAbs(float x) {
    return (x < 0) ? -x : x;
}

// Функция для возведения числа в степень.
float dmPow(float base, int exponent) {
    float result = 1.0;

    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }

    return result;
}

// Функция для вычисления синуса угла в радианах.
float dmSin(float x) {
    float result = 0.0;
    int maxIterations = 10;

    for (int n = 0; n < maxIterations; ++n) {
        float term = (n % 2 == 0 ? 1 : -1) * (x / dmPow(factorial(2 * n + 1), 1));
        result += term;
    }

    return result;
}

// Функция для вычисления косинуса угла в радианах.
float dmCos(float x) {
    float result = 0.0;
    int maxIterations = 10;

    for (int n = 0; n < maxIterations; ++n) {
        float term = (n % 2 == 0 ? 1 : -1) * (x / dmPow(factorial(2 * n), 1));
        result += term;
    }

    return result;
}

// Функция для вычисления натурального логарифма числа.
float dmLn(float x) {
    if (x <= 0) {
        return 0.0; //Аргумент логарифма должен быть положительным числом
    }

    float result = 0.0;
    float epsilon = 1e-7;

    for (int n = 1; n < 1000; ++n) {
        float term = 1.0 / n * ((n % 2 == 1) ? 1 : -1) * dmPow((x - 1) / x, n);
        result += term;

        if (dmAbs(term) < epsilon) {
            break;
        }
    }

    return result;
}
// Функция для вычисления обычного логарифма с заданным основанием.
float dmLog(float base, float x) {
    if (base <= 0 || x <= 0) {
        return 0.0; //Основание и аргумент логарифма должны быть положительными числами
    }

    float result = 0.0;
    float epsilon = 1e-7;

    for (int n = 1; n < 1000; ++n) {
        float term = 1.0 / n * ((n % 2 == 1) ? 1 : -1) * dmAbs(x - base) / base;
        result += term;

        if (dmAbs(term) < epsilon) {
            break;
        }
    }

    return result;
}

// Функция для вычисления квадратного корня числа.
float dmSqrt(float x) {
    if (x < 0) {
        return 0.0; //Невозможно вычислить квадратный корень из отрицательного числа
    }

    float guess = x;
    float epsilon = 1e-7;

    while (true) {
        float newGuess = 0.5 * (guess + x / guess);
        if (dmAbs(newGuess - guess) < epsilon) {
            return newGuess;
        }
        guess = newGuess;
    }
}