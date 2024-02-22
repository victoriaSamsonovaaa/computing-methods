#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <limits>

std::vector<double> relaxationMethod(const std::vector<std::vector<double>>& A, const std::vector<double>& b, double w, double epsilon, int& iterations) {
    int n = A.size(); // Размерность матрицы
    std::vector<double> x_k(n, 0.0); // Вектор начального приближения x_0 = {0, 0, ..., 0}

    // Метод релаксации
    iterations = 0; // Переменная для хранения числа итераций
    while (true) {
        iterations++; // Повышаем число итераций
        std::vector<double> x_k1(x_k); // Вектор-переменная для хранения (k+1)-ой итерации
        for (int i = 0; i < n; i++) {
            double firstSummary = 0;
            double secondSummary = 0;
            for (int j = 0; j < i; j++) {
                firstSummary += A[i][j] * x_k1[j]; // Подсчет первой суммы в формуле (2)
            }
            for (int j = i + 1; j < n; j++) {
                secondSummary += A[i][j] * x_k[j]; // Подсчет второй суммы в формуле (2)
            }
            double temp = (1 - w) * x_k[i] - (w / A[i][i]) * (firstSummary + secondSummary - b[i]); // Формула (2)

            // Проверка на наличие ошибок округления или деления на ноль
            if (std::isnan(temp) || std::isinf(temp)) {
                std::cout << "Error: Unable to converge. Check matrix A and vector b." << std::endl;
                return x_k;
            }

            x_k1[i] = temp;
        }
        double residual = std::sqrt(std::inner_product(x_k1.begin(), x_k1.end(), x_k1.begin(), 0.0)); // Вычисление нормы невязки

        // Проверка условия остановки итерационного процесса
        if (residual <= epsilon || iterations >= std::numeric_limits<int>::max()) {
            break;
        }
        x_k = x_k1; // Переносим значение из (k+1)-ой итерации в k-ую
    }
    return x_k; // Сохраняем результат для возвращения из функции
}

int main() {
    std::vector<std::vector<double>> A = {{4.0, 0.0, -1.0, 0.0, -1.0},
                                          {0.0, 5.0, -2.0, -1.0, 0.0},
                                          {-1.0, -2.0, 6.0, 0.0, -1.0},
                                          {0.0, -1.0, 0.0, 7.0, 0.0},
                                          {-1.0, 0.0, -1.0, 0.0, 8.0}}; // Пример матрицы A
    std::vector<double> b = {16.0, 12.0, 4.0, 10.0, 0.0}; // Пример вектора b
    double epsilon = 0.0001; // Пример заданной точности

    int minIterations = std::numeric_limits<int>::max();
    double bestOmega = 0.0;

    for (double w = 0.1; w <= 1.9; w += 0.01) {
        int iterations = 0;
        std::vector<double> result = relaxationMethod(A, b, w, epsilon, iterations);

        if (iterations < minIterations) {
            minIterations = iterations;
            bestOmega = w;
        }
    }

    std::cout << "Minimum iterations required: " << minIterations << std::endl;
    std::cout << "Best omega parameter: " << bestOmega << std::endl;

    return 0;
}
