#include <iostream>
#include "huber_distribution.h"
#include "empirical_distribution.h"
#include "mixture_distribution.h"
#include "interface.h"
// Функция для проверки значений с заданной точностью
void checkApprox(double actual, double expected, double epsilon, const std::string& message) {
    if (std::abs(actual - expected) > epsilon) {
        std::cout << "Test failed: " << message << ". Expected: " << expected << ", but got: " << actual << std::endl;
    }
    else {
        std::cout << "Test passed: " << message << std::endl;
    }
}
// Функция для запуска тестов
void runTests() {
    HuberDistribution* HB = new HuberDistribution();
    // Тест для v = 0.5
    HB->v = 0.5;
    HB->K = K(HB->v);
    HB->scale = 1.;
    HB->shift = 0.;
    checkApprox(huber_variance(HB), 8.08, 0.01, "Variance for v=0.5");
    checkApprox(huber_kurtosis(HB), 2.94, 0.01, "Kurtosis for v=0.5");
    checkApprox(P(HB), 0.214, 0.01, "Probability for v=0.5");
    checkApprox(Huber(0., HB), 0.223, 0.01, "Huber(0) for v=0.5");
    // Тест для v = 0.75
    HB->v = 0.75;
    HB->K = K(HB->v);
    checkApprox(huber_variance(HB), 3.71, 0.01, "Variance for v=0.75");
    checkApprox(huber_kurtosis(HB), 2.75, 0.01, "Kurtosis for v=0.75");
    checkApprox(P(HB), 0.405, 0.01, "Probability for v=0.75");
    checkApprox(Huber(0., HB), 0.296, 0.01, "Huber(0) for v=0.75");
    // Тест для v = 1
    HB->v = 1;
    HB->K = K(HB->v);
    checkApprox(huber_variance(HB), 2.24, 0.01, "Variance for v=1");
    checkApprox(huber_kurtosis(HB), 2.37, 0.01, "Kurtosis for v=1");
    checkApprox(P(HB), 0.585, 0.01, "Probability for v=1");
    checkApprox(Huber(0., HB), 0.342, 0.01, "Huber(0) for v=1");
    // Тест для v = 1.5
    HB->v = 1.5;
    HB->K = K(HB->v);
    checkApprox(huber_variance(HB), 1.31, 0.01, "Variance for v=1.5");
    checkApprox(huber_kurtosis(HB), 1.30, 0.01, "Kurtosis for v=1.5");
    checkApprox(P(HB), 0.834, 0.01, "Probability for v=1.5");
    checkApprox(Huber(0., HB), 0.384, 0.01, "Huber(0) for v=1.5");
    // Тест для v = 2
    HB->v = 2;
    HB->K = K(HB->v);
    checkApprox(huber_variance(HB), 1.08, 0.01, "Variance for v=2");
    checkApprox(huber_kurtosis(HB), 0.51, 0.01, "Kurtosis for v=2");
    checkApprox(P(HB), 0.946, 0.01, "Probability for v=2");
    checkApprox(Huber(0., HB), 0.396, 0.01, "Huber(0) for v=2");
    // Тест для v = 2.5
    HB->v = 2.5;
    HB->K = K(HB->v);
    checkApprox(huber_variance(HB), 1.02, 0.01, "Variance for v=2.5");
    checkApprox(huber_kurtosis(HB), 0.16, 0.1, "Kurtosis for v=2.5");
    checkApprox(P(HB), 0.986, 0.01, "Probability for v=2.5");
    checkApprox(Huber(0., HB), 0.398, 0.01, "Huber(0) for v=2.5");
    // Тест для v = 3
    HB->v = 3;
    HB->K = K(HB->v);
    checkApprox(huber_variance(HB), 1.00, 0.01, "Variance for v=3");
    checkApprox(huber_kurtosis(HB), 0.04, 0.01, "Kurtosis for v=3");
    checkApprox(P(HB), 0.997, 0.01, "Probability for v=3");
    checkApprox(Huber(0., HB), 0.399, 0.01, "Huber(0) for v=3");
    delete HB; // Освобождаем память
}
int main() {
    setlocale(LC_ALL, "Russian");
    interface(); // Вызов функции интерфейса
    runTests();  // Запуск тестов
    
    return 0; // Завершение программы
}