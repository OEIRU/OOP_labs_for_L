#include "Interface.h"

void step2(const Primary* HB)
{
	ofstream x_s;
	ofstream y_s;
	ofstream params;
	vector<pair<double, double>> table;
	char option;
	int n;
	double x = 0;

	cout << "Что делаем дальше?" << endl;
	cout << "1. Вывести параметры распределения на экран" << endl;
	cout << "2. Вычислить значение плотности распределения в произвольной точке" << endl;
	cout << "3. Получить выборку для анализа" << endl;
	cout << "4. Вывести параметры распределения в файл" << endl << endl;


	cin >> option;
	cout << endl;

	switch(option)
	{
	case '1':
		cout << "v = " << HB->get_v() << endl;
		cout << "K = " << HB->get_k() << endl;
		cout << "Scale = " << HB->get_scale() << endl;
		cout << "Shift = " << HB->get_shift() << endl;
		cout << "M[X] = " << HB->expected_value() << endl;
		cout << "D[X] = " << HB->variance() << endl;
		cout << "As[X] = " << HB->asymmetry() << endl;
		cout << "Kurt[X] = " << HB->kurtosis() << endl;
		cout << "P = " << HB->P() << endl;
		cout << "f(0) = " << HB->f(0) << endl;

		break;

	case '2':
		cout << "Введите x: ";
		cin >> x;
		cout << endl << "f(" << x << ") = " << HB->f(x) << endl;
		break;

	case '3':
		x_s.open("x_s.txt");
		y_s.open("y_s.txt");
		cout << "Введите размерность выборки n: ";
		cin >> n;
		table = HB->generate_table_of_values(n);
		for (const pair<double, double>& pr : table)
		{
			x_s << pr.first << endl;
			y_s << pr.second << endl;
		}

		x_s.close();
		x_s.close();

		cout << endl << "Значения выборки записаны в файлы x_s.txt и y_s.txt" << endl;
		break;

	case '4':
		HB->save_to_file(params);
		break;

	default:
		cerr << endl << "Ошибка: Некорректный параметр" << endl;
		break;
	}
}

void step1()
{
	char option;
	double v, scale, shift;
	Primary* HB;
	ifstream file;

	cout << "Выберите опцию: " << endl;
	cout << "1. Стандартное распределение Хьюбера" << endl;
	cout << "2. Ввести произвольные параметры с клавиатуры" << endl;
	cout << "3. Считать параметры из файла" << endl << endl;

	cin >> option;
	cout << endl;

	switch(option)
	{
	case '1':
		cout << "Введите параметр v: ";
		cin >> v;
		cout << endl;
		try 
		{
			HB = new Primary(v);
		}
		catch (exception e)
		{
			cerr << e.what() << endl;
			exit(1);
		}

		step2(HB);
		break;

	case '2':
		cout << "Введите v lambda mu: ";
		cin >> v >> scale >> shift;
		cout << endl;
		try
		{
			HB = new Primary(v, scale, shift);
		}
		catch(exception e)
		{
			cerr << e.what() << endl;
			exit(1);
		}

		step2(HB);
		break;

	case '3':
		try
		{
			HB = new Primary(file);
		}
		catch (exception e)
		{
			cerr << endl << e.what() << endl;
			exit(1);
		}

		step2(HB);
		break;

	default:
		cerr << endl << "Ошибка: Некорректный параметр" << endl;
		exit(1);
	}
}

void start()
{
	step1();
}