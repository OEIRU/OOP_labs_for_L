#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<double> read_data(const string& filename) {
    vector<double> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return data;
    }
    string line;
    while (getline(file, line)) {
        try {
            double value = stod(line);
            data.push_back(value);
        } catch (const exception& e) {
            cerr << "Ошибка чтения строки: " << line << endl;
        }
    }
    return data;
}

int main() {
    // Чтение данных
    vector<double> empirical = read_data("data/fs_empirical.txt");
    vector<double> theoretical = read_data("data/fs_theoretical.txt");

    if (empirical.empty() || theoretical.empty()) {
        cerr << "Нет данных для построения графика." << endl;
        return 1;
    }

    // Сохранение данных во временные файлы
    ofstream emp_file("temp_empirical.dat");
    ofstream theo_file("temp_theoretical.dat");

    if (!emp_file || !theo_file) {
        cerr << "Ошибка создания временных файлов." << endl;
        return 1;
    }

    for (size_t i = 0; i < empirical.size(); ++i) {
        emp_file << i << " " << empirical[i] << endl;
    }
    for (size_t i = 0; i < theoretical.size(); ++i) {
        theo_file << i << " " << theoretical[i] << endl;
    }

    emp_file.close();
    theo_file.close();

    // Создание скрипта для GNUplot
    ofstream script("plot_script.gp");
    if (!script) {
        cerr << "Ошибка создания скрипта." << endl;
        return 1;
    }

    script << "set terminal pngcairo enhanced font 'arial,10'\n";
    script << "set output 'comparison_plot.png'\n";
    script << "set xlabel 'Индекс'\n";
    script << "set ylabel 'Значение'\n";
    script << "set title 'Сравнение эмпирических и теоретических данных'\n";
    script << "plot 'temp_empirical.dat' w lines title 'Эмпирические', ";
    script << "'temp_theoretical.dat' w lines title 'Теоретические'\n";

    script.close();

    // Запуск GNUplot
    system("gnuplot plot_script.gp");

    // Очистка временных файлов
    remove("temp_empirical.dat");
    remove("temp_theoretical.dat");
    remove("plot_script.gp");

    cout << "График сохранен в файл comparison_plot.png" << endl;

    return 0;
}