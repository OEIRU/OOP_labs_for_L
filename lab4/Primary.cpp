#include "Primary.h"

Primary::Primary(double v, double scale, double shift)
{
    if (v <= 0 || scale <= 0)
        throw invalid_argument("Ошибка: один или несколько параметров не корректны");

    this->v = v;
    this->k = K(v);
    this->scale = scale;
    this->shift = shift;
}

Primary::Primary(ifstream& file)
{
    load_from_file(file);
}

void Primary::save_to_file(ofstream& file)
{
    string filename;
    cout << "Введите имя файла, куда следует записать параметры основного распределения: ";
    cin >> filename;

    file.open(filename);
    file << this->v << endl << this->scale << endl << this->shift;
    file.close();

    cout << "Параметры основного распределения сохранены в файл " + filename << endl;
}

void Primary::load_from_file(ifstream& file)
{
    string filename;
    double v, scale, shift;

    cout << "Введите имя файла, откуда следует считать параметры основного распределения: ";
    cin >> filename;

    file.open(filename);

    if (!file)
        throw runtime_error("Ошибка: не удалось открыть файл");

    file >> v >> scale >> shift;

    file.close();

    if (v <= 0 || scale <= 0)
        throw invalid_argument("Ошибка: один или несколько параметров некорректны");

    this->v = v;
    this->scale = scale;
    this->shift = shift;
}


double Primary::get_v() const
{
    return this->v;
}

double Primary::get_k() const
{
    return this->k;
}


void Primary::set_v(double v)
{
    if (v <= 0)
        throw invalid_argument("Ошибка: v <= 0");

    this->v = v;
    this->k = K(this->v);
}

double Primary::get_scale() const
{
    return this->scale;
}

void Primary::set_scale(const double scale)
{
    if (scale <= 0)
        throw invalid_argument("Ошибка: scale <= 0");
    this->scale = scale;
}

double Primary::get_shift() const
{
    return this->shift;
}

void Primary::set_shift(const double shift)
{
    this->shift = shift;
}

double Primary::f(const double x) const
{
    return (1. / (sqrt(2. * M_PI) * this->k) * (abs((x - this->shift) / this->scale) <= this->v ? exp(-pow((x - this->shift) / this->scale, 2.) / 2.) : exp(pow(this->v, 2.) / 2. - this->v * abs((x - this->shift) / this->scale)))) / this->scale;
}

double Primary::phi(double x) const
{
    return 0.5 * (1. + erf(x / sqrt(2.)));
}

double Primary::phi_lower(double x) const
{
    return 1. / sqrt(2. * M_PI) * exp(-1. / 2. * pow(x, 2.));
}

double Primary::expected_value() const
{
    return this->shift;
}

double Primary::variance() const
{
    return 1. + 2. * phi_lower(this->v) * (pow(this->v, 2.) + 2.) / (pow(this->v, 3.) * this->k);
}

double Primary::asymmetry() const
{
    return 0.;
}

double Primary::kurtosis() const
{
    return (3. * (2. * phi(this->v) - 1.) + 2. * phi_lower(this->v) * (24. / pow(this->v, 5.) + 24. / pow(this->v, 3.) + 12. / this->v + this->v)) / (pow(variance(), 2.) * this->k) - 3.;
}

double Primary::P() const
{
    return (2. * phi(this->v) - 1.) / this->k;
}

double Primary::K(const double v) const
{
    return 2. / v * phi_lower(v) + 2. * phi(v) - 1.;
}

double Primary::random_var() const
{
    random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<> d(0, 1);

    //шаг 1
    double r1 = d(gen);


    if (r1 <= P())
    {
        //шаг 2
        double r2, r3, x1;

        do {
            r2 = d(gen);
            r3 = d(gen);
            x1 = sqrt(-2 * log(r2)) * cos(2 * M_PI * r3);
            //double x1 = sqrt(-2 * log(r2)) * sin(2 * M_PI * r3)
        } while (!(-this->v <= x1 && x1 <= this->v)); //шаг 3

        return x1 * this->scale + this->shift;
    }
    else
    {
        //шаг 4
        double r4 = d(gen);
        double x2 = this->v - log(r4) / this->v;

        //шаг 5
        return r1 < (1 + P()) / 2 ? x2 * this->scale + this->shift : -x2 * this->scale + this->shift;
    }
}

vector<double> Primary::generate_sequence(const int n) const
{
    vector<double> res;

    for (int i = 0; i < n; i++)
    {
        double x = random_var();
        res.push_back(x);
    }

    sort(res.begin(), res.end());

    return res;
}

vector<pair<double, double>> Primary::generate_table_of_values(const int n, const vector<double>& x_s) const
{
    vector<pair<double, double>> res;
    vector<double> sequence;

    if (x_s.empty())
        sequence = generate_sequence(n);
    else
        sequence = x_s;

    for (const double& x : sequence)
    {
        double y = f(x);
        res.push_back(make_pair(x, y));
    }

    return res;
}