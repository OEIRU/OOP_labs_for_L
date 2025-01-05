#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include "Interface.h"

void demo() {
    std::cout << "7. Тест позднего связывания:" << std::endl << std::endl;

    Primary* HB1 = new Primary(1, 1, 2);
    Primary* HB2 = new Primary(1, 2, 6);
    Primary* HB3 = new Primary(1, 2, -6);
    Primary* HB4 = new Primary(1, 1, -2);

    Mixture<Primary, Primary>* MX1 = new Mixture<Primary, Primary>(HB1, HB2, 0.5);
    Mixture<Primary, Primary>* MX2 = new Mixture<Primary, Primary>(HB3, HB4, 0.5);
    Mixture<Mixture<Primary, Primary>, Mixture<Primary, Primary>>* MX = new Mixture<Mixture<Primary, Primary>, Mixture<Primary, Primary>>(MX1, MX2, 0.5);

    std::cout << "Параметр формы 1: " << MX->get_component1()->get_component1()->get_v() << std::endl;
    std::cout << "Параметр масштаба 1: " << MX->get_component1()->get_component1()->get_scale() << std::endl;
    std::cout << "Параметр сдвига 1: " << MX->get_component1()->get_component1()->get_shift() << std::endl << std::endl;

    std::cout << "Параметр формы 2: " << MX->get_component1()->get_component2()->get_v() << std::endl;
    std::cout << "Параметр масштаба 2: " << MX->get_component1()->get_component2()->get_scale() << std::endl;
    std::cout << "Параметр сдвига 2: " << MX->get_component1()->get_component2()->get_shift() << std::endl << std::endl;

    std::cout << "Параметр формы 3: " << MX->get_component2()->get_component1()->get_v() << std::endl;
    std::cout << "Параметр масштаба 3: " << MX->get_component2()->get_component1()->get_scale() << std::endl;
    std::cout << "Параметр сдвига 3: " << MX->get_component2()->get_component1()->get_shift() << std::endl << std::endl;

    std::cout << "Параметр формы 4: " << MX->get_component2()->get_component2()->get_v() << std::endl;
    std::cout << "Параметр масштаба 4: " << MX->get_component2()->get_component2()->get_scale() << std::endl;
    std::cout << "Параметр сдвига 4: " << MX->get_component2()->get_component2()->get_shift() << std::endl << std::endl;

    std::cout << "Теоретические характеристики:" << std::endl;
    std::cout << "Математическое ожидание: " << MX->expected_value() << std::endl;
    std::cout << "Дисперсия: " << MX->variance() << std::endl;
    std::cout << "Коэффициент асимметрии: " << MX->asymmetry() << std::endl;
    std::cout << "Коэффициент эксцесса: " << MX->kurtosis() << std::endl << std::endl;

    Empirical* EM1 = new Empirical(MX, 10000, 0);
    Empirical* EM2 = new Empirical(MX, 10000, 0);

    std::cout << "Эмпирические характеристики:" << std::endl;
    std::cout << "Математическое ожидание: " << MX->expected_value() << std::endl;
    std::cout << "Дисперсия: " << MX->variance() << std::endl;
    std::cout << "Коэффициент асимметрии: " << MX->asymmetry() << std::endl;
    std::cout << "Коэффициент эксцесса: " << MX->kurtosis() << std::endl << std::endl;

    std::vector<std::pair<double, double>> s1 = MX->generate_table_of_values(10000, MX->generate_sequence(10000));
    std::vector<std::pair<double, double>> s2 = EM1->generate_table_of_values(10000, EM1->generate_sequence(10000));
    std::vector<std::pair<double, double>> s3 = EM2->generate_table_of_values(10000, EM2->generate_sequence(10000));

    std::ofstream file1("theoretical.txt");
    std::ofstream file2("empirical.txt");
    std::ofstream file3("empirical2.txt");

    for (auto& s : s1)
        file1 << s.second << std::endl;
    for (auto& s : s2)
        file2 << s.second << std::endl;
    for (auto& s : s3)
        file3 << s.second << std::endl;

    file1.close();
    file2.close();
    file3.close();
}

int main(int argc, char** argv) {
    std::setlocale(LC_ALL, "ru");

    // Раскомментируйте для запуска демо-функции
    // demo();

    start();

    return 0;
}