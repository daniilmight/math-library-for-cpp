# DM Math Lib

DM Math Lib это библиотека на C, предоставляющая реализации различных математических функций без использования внешних библиотек.

## Описание

Комментарии к функциям указаны в коде библиотеке.

Эта библиотека предоставляет следующие математические функции:

### `dmAbs`: Вычисляет модуль числа.

Функция dmAbs вычисляет модуль числа x. Если x отрицательно, то функция возвращает его отрицательное значение, иначе возвращает само число. Модуль числа представляет собой его абсолютное значение, то есть его значение без учета знака.

  ```
  double dmAbs(double x) {
      return (x < 0) ? -x : x;
  }
  ```
### `dmPow`: Возводит число в заданную степень.

Функция dmPow принимает два аргумента: base (основание) и exponent (показатель степени), и возвращает значение base, возведенное в степень exponent. Она использует цикл for для последовательного умножения base на себя exponent раз. Полученное произведение является результатом операции возведения в степень.
  ```
  double dmPow(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
  }
  ```
### `dmMod`: Функция для вычисления остатка от деления.

$$
result = x - y * (\frac{x}{y})
$$

Функция dmMod вычисляет остаток от деления числа x на число y. Она использует операцию целочисленного деления, чтобы найти количество полных частей y, которые помещаются в x, затем вычитает произведение этого количества на y из x, чтобы получить остаток. Таким образом, результатом является остаток от деления x на y.
  ```
  double dmMod(double x, double y) {
    return x - y * int(x / y);
  }
  ```
### `dmSin`: Вычисляет синус угла в радианах с помощью ряда Тейлора для синуса.

$$
\sin(x) = \sum_{n=0}^{\infty} \frac{(-1)^n x^{2n+1}}{(2n+1)!}
$$

Функция dmSin вычисляет синус угла x в радианах с использованием ряда Тейлора для синуса. Знак угла x определяется, затем значение угла приводится к интервалу от 0 до 2π. Если угол x превышает π, он корректируется, а также корректируется его знак. Затем идет инициализация переменных sin (синус) и term (текущий член ряда) равными значению угла x.

Итерационный процесс вычисляет дополнительные члены ряда Тейлора до тех пор, пока абсолютное значение текущего члена ряда превышает заданную точность eps. Каждый член ряда вычисляется на основе формулы ряда Тейлора для синуса.

Наконец, результат умножается на знак угла и возвращается функцией в качестве синуса угла x.
  ```
  double dmSin(double x) {
    int sign = (x < 0) ? -1 : 1;

    x = dmMod(dmAbs(x), 2 * pi);

    if (x > pi) {
        x -= pi;
        sign *= -1;
    }

    double sum = x, term = x;

    for (int n = 3; dmAbs(term) > eps; n += 2) {
        term = -term * x * x / n / (n - 1);
        sum += term;
    }
    return sum * sign;
  }
  ```
### `dmCos`: Вычисляет косинус угла в радианах с помощью ряда Тейлора для косинуса.

$$
\cos(x) = \sum_{n=0}^{\infty} \frac{(-1)^n x^{2n}}{(2n)!}
$$

Функция dmCos вычисляет косинус угла x в радианах с использованием ряда Тейлора для косинуса. Сначала значение угла x приводится к интервалу [0, 2π) для обеспечения периодичности косинуса. Затем инициализируются переменные для суммы ряда и текущего члена ряда. Итеративно вычисляются члены ряда Тейлора для косинуса до тех пор, пока абсолютное значение текущего члена превышает заданную точность eps. каждый следующий член ряда вычисляется на основе предыдущего, используя формулу ряда Тейлора для косинуса. Результатом функции является сумма всех членов ряда, что представляет собой приближенное значение косинуса угла x.
  ```
  double dmCos(double x){
    x = dmMod(dmAbs(x), 2 * pi);

    double sum = 1, term = 1;

    for (int n = 0; dmAbs(term) > eps; n++) {
        term = -(term * x * x) / ((2 * n + 2) * (2 * n + 1));
        sum += term; // Обновляем сумму ряда.
    }
    return sum;
  }
  ```
### `dmLn`: Вычисляет натуральный логарифм числа с помощью ряда Тейлора.

$$
\ln(1 + x) = \sum_{n=1}^{\infty} \frac{(-1)^{n+1} x^n}{n}
$$

Функция dmLn вычисляет натуральный логарифм числа x с использованием ряда Тейлора. В начале проверяется, является ли аргумент x отрицательным или нулевым. Если это так, функция возвращает ноль. Затем аргумент x приводится к разумному диапазону от 0.25 до 1, делением или умножением на e, и соответствующее количество единиц добавляется к переменной power_adjust. Далее x уменьшается на единицу для упрощения дальнейших вычислений. Затем вычисляется сумма ряда Тейлора для натурального логарифма с помощью итераций до n=20. Каждый член ряда представляет собой следующее значение аргумента x в степени n, деленное на n, с учетом знака. Результатом является приближенное значение натурального логарифма числа x, скорректированное на power_adjust.
  ```
  double dmLn(double x) {
    if (x <= 0) {
        return 0;
    }

    int power_adjust = 0;
    while (x > 1.0) {
        x /= e;
        power_adjust++;
    }
    while (x < 0.25) {
        x *= e;
        power_adjust--;
    }

    x -= 1.0;
    double sum = 0.0, sign = 1.0, term = x;
    for (int k = 1; k <= 20; k++) {
        sum += term * sign / k;
        term *= x;
        sign = -sign;
    }
    return sum + power_adjust;
  }
  ```
### `dmLog`: Вычисляет логарифм числа по заданному основанию с помощью ряда Тейлора.

$$
\log_a(x) = \frac{\ln(x)}{\ln(a)}
$$

Функция dmLog вычисляет логарифм числа x по заданному основанию b с использованием ряда Тейлора. Сначала проверяется, являются ли основание b и аргумент x отрицательными или нулевыми значениями. Если это так, функция возвращает ноль, поскольку логарифм не определен для отрицательных или нулевых аргументов. Затем функция вычисляет логарифм числа x по основанию e (натуральный логарифм) и логарифм основания b по тому же основанию e. Результатом является отношение натуральных логарифмов числа x и основания b, что представляет собой логарифм числа x по основанию b.
  ```
  double dmLog(double x, double base) {
    if (base <= 0 || x <= 0) {
        return 0.0;
    }

    double result = dmLn(x) / dmLn(base);
    return result;
  }
  ```
### `dmSqrt`: Вычисляет квадратный корень числа с помощью метода Ньютона.

$$
x_{n+1} = \frac{1}{2} \left( x_n + \frac{S}{x_n} \right)
$$

Функция dmSqrt вычисляет квадратный корень числа x с использованием метода Ньютона. Сначала проверяется, является ли число x отрицательным. Если это так, функция возвращает 0, поскольку квадратный корень не определен для отрицательных чисел. Затем функция начинает итерационный процесс, чтобы приблизиться к корню. Начальное предположение guess устанавливается равным x. Затем на каждой итерации вычисляется новое предположение newGuess с помощью формулы Ньютона. Если разница между текущим и предыдущим предположениями меньше заданной точности eps, функция возвращает новое предположение. Иначе текущее предположение обновляется новым итерационным значением newGuess. Если максимальное количество итераций исчерпано, функция также возвращает текущее предположение.
```
  double dmSqrt(double x) {
    if (x < 0) {
        return 0.0;
    }

    double guess = x;
    double newGuess;
    int maxIterations = 1000;

    while (maxIterations--) {
        newGuess = 0.5 * (guess + x / guess);
        if (dmAbs(newGuess - guess) < eps) {
            return newGuess;
        }
        guess = newGuess;
    }

    return guess;
}
```


