#include <iostream>
#include "huber_distribution.h"
#include "empirical_distribution.h"
#include "mixture_distribution.h"
#include "interface.h"
#include "tests.h"

int main() {
    setlocale(LC_ALL, "Russian");
    interface(); // Вызов функции интерфейса
    runTests();  // Запуск тестов
    
    return 0; // Завершение программы
}