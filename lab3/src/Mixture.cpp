#include "Mixture.h"

Mixture::Mixture() : p(0.5)
{
	HB1 = new Primary(1, 1, 0);
	HB2 = new Primary(1, 1, 0);
}

Mixture::Mixture(Primary* _HB1, Primary* _HB2, double _p) :
	HB1(_HB1), HB2(_HB2), p(_p > 0 and _p < 1 ? _p : throw invalid_argument("Ошибка: один или несколько параметров некорректны") ) {}

Mixture::Mixture(ifstream& file)
{
	double v1, scale1, shift1, v2, scale2, shift2, p;
	string filename;
	cout << "Введите имя файла: ";
	cin >> filename;
	file.open(filename);

	if (!file) 
		throw runtime_error("Ошибка: не удалось открыть файл");

	file >> p >> v1 >> scale1 >> shift1 >> v2 >> scale2 >> shift2;
	file.close();

	if (p > 1 || p < 0 || v1 <= 0 || v2 <= 0 || scale1 <= 0 || scale2 <= 0)
		throw invalid_argument("Ошибка: один или несколько параметров не корректны");

	HB1 = new Primary(v1, scale1, shift1);
	HB2 = new Primary(v2, scale2, shift2);

	this->p = p;
}

Primary* Mixture::get_component1()
{
	return HB1;
}

Primary* Mixture::get_component2()
{
	return HB2;
}

double Mixture::get_p() const
{
	return p;
}

void Mixture::set_p(const double p)
{
	if (p > 1 || p < 0)
		throw invalid_argument("Ошибка: один параметро некорректен");

	this->p = p;
}

void Mixture::save_to_file(ofstream& file)
{
	string filename;
	cout << "Введите имя выходного файла: ";
	cin >> filename;
	file.open(filename);

	file << p << endl << HB1->get_v() << endl << HB1->get_scale() << endl << HB1->get_shift() << endl << HB2->get_v() << endl << HB2->get_scale() << endl << HB2->get_shift();
	file.close();

	cout << endl << "Параметры распределения сохранены в файл " + filename << endl;
}

double Mixture::f(const double x) const
{
	return (1 - p) * HB1->f(x) + p * HB2->f(x);
}

double Mixture::expected_value() const
{
	return (1 - p) * HB1->expected_value() + p * HB2->expected_value();
}

double Mixture::variance() const
{
	return (1 - p) * (pow(HB1->expected_value(), 2) + HB1->variance()) +
		p * (pow(HB2->expected_value(), 2) + HB2->variance()) -
		pow(expected_value(), 2);
}

double Mixture::asymmetry() const
{
	return ((1 - p) * (pow((HB1->expected_value() - expected_value()), 3) + 3 * (HB1->expected_value() - expected_value()) * HB1->variance() + pow(HB1->variance(), 3 / 2) * HB1->asymmetry()) +
		p * (pow((HB2->expected_value() - expected_value()), 3) + 3 * (HB2->expected_value() - expected_value()) * HB2->variance() + pow(HB2->variance(), 3 / 2) * HB2->asymmetry())) /
		pow(variance(), 3 / 2);
}

double Mixture::kurtosis() const
{
	return ((1 - p) * (pow((HB1->expected_value() - expected_value()), 4) + 6 * HB1->variance() * pow((HB1->expected_value() - expected_value()), 2) +
		4 * (HB1->expected_value() - expected_value()) * pow(HB1->variance(), 3 / 2) * HB1->asymmetry() + pow(HB1->variance(), 2) * HB1->kurtosis()) +
		p * (pow((HB2->expected_value() - expected_value()), 4) + 6 * HB2->variance() * pow((HB2->expected_value() - expected_value()), 2) +
			4 * (HB2->expected_value() - expected_value()) * pow(HB2->variance(), 3 / 2) * HB2->asymmetry() + pow(HB2->variance(), 2) * HB2->kurtosis()) - 3) /
		pow(variance(), 2);
}

double Mixture::random_var() const {
	random_device rd;
	default_random_engine gen(rd());
	uniform_real_distribution<> d(0, 1);

	double r = d(gen);

	if (r > p) 
		return HB1->random_var();
	else 
		return HB2->random_var();
}

vector<double> Mixture::generate_sequence(const int n) const
{
	vector<double> sequence;
	for (int i = 0; i < n; i++)
	{
		double x = random_var();
		sequence.push_back(x);
	}

	sort(sequence.begin(), sequence.end());
	return sequence;
}

vector<pair<double, double>> Mixture::generate_table_of_values(const int n, const vector<double>& x_s) const
{
	vector<double> sequence;
	vector<pair<double, double>> table;

	if (x_s.empty())
		sequence = generate_sequence(n);
	else
		sequence = x_s;

	for (const double& x : sequence)
	{
		double y = f(x);
		table.push_back(make_pair(x, y));
	}

	return table;
}
