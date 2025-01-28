#include "interface.h"
#include <empirical_distribution.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Helper function to create a uniform grid of x values
vector<double> create_uniform_grid(double min_x, double max_x, int num_points) {
    vector<double> grid;
    double step = (max_x - min_x) / (num_points - 1);
    for (int i = 0; i < num_points; ++i) {
        grid.push_back(min_x + i * step);
    }
    return grid;
}

// Helper function to write distribution data to files
void write_distribution_data(const vector<double>& x_grid, const vector<double>& theoretical_values, const vector<double>& empirical_values) {
    ofstream xs("data/xs.txt");
    ofstream fs_theoretical("data/fs_theoretical.txt");
    ofstream fs_empirical("data/fs_empirical.txt");

    if (!xs.is_open() || !fs_theoretical.is_open() || !fs_empirical.is_open()) {
        cerr << "Ошибка открытия файлов для записи!" << endl;
        return;
    }

    for (size_t i = 0; i < x_grid.size(); ++i) {
        xs << x_grid[i] << endl;
        fs_theoretical << theoretical_values[i] << endl;
        fs_empirical << empirical_values[i] << endl;
    }

    xs.close();
    fs_theoretical.close();
    fs_empirical.close();

    cout << "Данные успешно записаны в файлы." << endl;
}

// Function to calculate and output distribution statistics
void output_distribution_stats(int n, const vector<double>& x_s, HuberDistribution* HB, double x) {
    cout << "Для основного распределения:" << endl;
    cout << "Математическое ожидание: " << huber_expected_value(HB) << endl;
    cout << "Дисперсия: " << huber_variance(HB) << endl;
    cout << "Коэффициент асимметрии: " << huber_asymmetry(HB) << endl;
    cout << "Коэффициент эксцесса: " << huber_kurtosis(HB) << endl;
    cout << "Значение плотности в точке " << x << ": " << Huber(x, HB) << endl << endl;

    cout << "Для эмпирического распределения:" << endl;
    cout << "Математическое ожидание: " << empirical_expected_value(n, x_s) << endl;
    cout << "Дисперсия: " << empirical_variance(n, x_s) << endl;
    cout << "Коэффициент асимметрии: " << empirical_asymmetry(n, x_s) << endl;
    cout << "Коэффициент эксцесса: " << empirical_kurtosis(n, x_s) << endl;
    cout << "Значение плотности в точке " << x << ": " << empirical_huber(n, x, x_s) << endl;
}

// Function to handle file output for a distribution
void handle_file_output(int n, const vector<double>& x_s, HuberDistribution* HB, bool is_mixture = false, Mixture* M = nullptr) {
    double min_x = *min_element(x_s.begin(), x_s.end());
    double max_x = *max_element(x_s.begin(), x_s.end());
    vector<double> x_grid = create_uniform_grid(min_x, max_x, 1000);

    vector<double> theoretical_values, empirical_values;
    for (double x : x_grid) {
        theoretical_values.push_back(is_mixture ? mixture(x, M) : Huber(x, HB));
        empirical_values.push_back(empirical_huber(n, x, x_s));
    }

    write_distribution_data(x_grid, theoretical_values, empirical_values);
}

// Function to work with the main distribution
void general_distribution() {
    int n = 1000;
    int distribution_params_option;
    int file_option;
    double v, scale, shift, x;
    vector<double> x_s;
    HuberDistribution* HB;

    cout << "Параметры распределения:" << endl
         << "1) Стандартное распределение" << endl
         << "2) Другие параметры" << endl;
    cin >> distribution_params_option;

    if (distribution_params_option == 1) {
        cout << "Введите v: ";
        cin >> v;
        scale = 1;
        shift = 0;
        x = 0;
    } else {
        cout << "Введите v, scale, shift, x: ";
        cin >> v >> scale >> shift >> x;
    }

    HB = init_huber_distribution(v, K(v), scale, shift);
    x_s = generate_sequence(n, HB);

    output_distribution_stats(n, x_s, HB, x);

    cout << "Вывести данные распределения в отдельный файл? (1 - Да, 0 - Нет): ";
    cin >> file_option;
    if (file_option) {
        handle_file_output(n, x_s, HB);
    }

    delete HB; // Освобождаем память
}

// Function to work with a mixture of distributions
void mixture_distribution() {
    int n = 1000;
    int file_option;
    double v1, scale1, shift1, v2, scale2, shift2, x, p;
    vector<double> x_s;
    Mixture* M;

    cout << "Введите v1, scale1, shift1, v2, scale2, shift2, p, x: ";
    cin >> v1 >> scale1 >> shift1 >> v2 >> scale2 >> shift2 >> p >> x;

    M = init_mixture(p, v1, v2, scale1, scale2, shift1, shift2);
    x_s = generate_sequence(n, M->HB1);

    output_distribution_stats(n, x_s, M->HB1, x);

    cout << "Вывести данные распределения в отдельный файл? (1 - Да, 0 - Нет): ";
    cin >> file_option;
    if (file_option) {
        handle_file_output(n, x_s, nullptr, true, M);
    }

    delete M; // Освобождаем память
}

// Main program interface
void interface() {
    int distribution_option;

    while (true) {
        cout << "С каким распределением работаем?" << endl
             << "1) Основное распределение" << endl
             << "2) Смесь распределений" << endl
             << "3) Выйти" << endl;
        cin >> distribution_option;

        switch (distribution_option) {
            case 1:
                general_distribution();
                break;
            case 2:
                mixture_distribution();
                break;
            case 3:
                return;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
}