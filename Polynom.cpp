#include <iostream>
#include <cassert>
using namespace std;

class Polynom
{
    friend ostream &operator<<(ostream &, const Polynom &);

private:
    int degree;
    double *coeff;
    static int objCount;
    void correctDegree();

public:
    Polynom();
    Polynom(int);
    Polynom(double *, int);
    Polynom(const Polynom &);
    ~Polynom();
    static int getObjCount();

    const Polynom &operator=(const Polynom &);
    double &operator[](int);
    double operator()(double) const;
    Polynom operator+(const Polynom &) const;
    Polynom operator*(const Polynom &) const;
    Polynom &operator+=(const Polynom &);
    Polynom &operator*=(const Polynom &);
    int getDegree() { return degree; }

    Polynom derivative(int = 1);
};

int Polynom::objCount = 0;

Polynom::Polynom()
{
    degree = 0;
    coeff = new double[1];
    coeff[0] = 0;
    ++objCount;
}

Polynom::Polynom(int n)
{
    degree = (n < 0 ? 0 : n);
    coeff = new double[degree + 1];
    assert(coeff);
    for (int i = 0; i <= degree; ++i)
        coeff[i] = 1;

    ++objCount;
}

Polynom::Polynom(double *c, int degree)
{
    if (c != NULL)
    {
        this->degree = (degree < 0 ? 0 : degree);
        coeff = new double[this->degree + 1];
        assert(coeff);
        for (int i = 0; i <= this->degree; ++i)
            coeff[i] = c[i];
    }
    else
    {
        degree = 0;
        coeff = new double[1];
        coeff[0] = 0;
    }
    ++objCount;
    correctDegree();
}

Polynom::Polynom(const Polynom &p)
{
    degree = p.degree;
    coeff = new double[degree + 1];
    assert(coeff);
    for (int i = 0; i <= this->degree; ++i)
    {
        coeff[i] = p.coeff[i];
    }

    ++objCount;
}

Polynom::~Polynom()
{
    --objCount;
    delete[] coeff;
}

int Polynom::getObjCount()
{
    return objCount;
}

const Polynom &Polynom::operator=(const Polynom &p)
{
    if (this != &p)
    {

        if (degree != p.degree)
        {
            degree = p.degree;
            delete[] coeff;
            coeff = new double[degree + 1];
            assert(coeff);
        }

        for (int i = 0; i <= degree; ++i)
        {
            coeff[i] = p.coeff[i];
        }
    }
    correctDegree();
    return *this;
}
double &Polynom::operator[](int index)
{
    if (index > degree)
    {
        double *newCoeff = new double[index + 1];
        assert(newCoeff);
        for (int i = 0; i <= degree; ++i)
            newCoeff[i] = coeff[i];
        for (int i = degree + 1; i <= index; ++i)
            newCoeff[i] = 0;
        degree = index;
        delete[] coeff;
        coeff = newCoeff;
    }
    return coeff[index < 0 ? 0 : index];
}

double Polynom::operator()(double x) const
{
    double s = coeff[degree];
    for (int i = degree - 1; i >= 0; --i)
    {
        s = s * x + coeff[i];
    }
    return s;
}

Polynom Polynom::operator+(const Polynom &p) const
{
    Polynom res(*this);
    res += p;
    return res;
}

Polynom Polynom::operator*(const Polynom &p) const
{
    Polynom res(*this);
    res *= p;
    return res;
}

Polynom &Polynom::operator+=(const Polynom &p)
{
    if (p.degree > degree)
    {
        double *newCoeff = new double[p.degree + 1];
        assert(newCoeff);
        for (int i = 0; i <= degree; ++i)
            newCoeff[i] = coeff[i];
        for (int i = degree + 1; i <= p.degree; ++i)
            newCoeff[i] = 0;
        degree = p.degree;
        delete[] coeff;
        coeff = newCoeff;
    }
    for (int i = 0; i <= p.degree; ++i)
    {
        coeff[i] += p.coeff[i];
    }
    correctDegree();
    return *this;
}

Polynom &Polynom::operator*=(const Polynom &p)
{
    int d = p.degree + degree;
    double *newCoeff = new double[d + 1];
    assert(newCoeff);
    for (int i = 0; i <= d; ++i)
        newCoeff[i] = 0;
    for (int i = 0; i <= p.degree; ++i)
    {
        for (int j = 0; j <= degree; ++j)
        {
            newCoeff[i + j] += p.coeff[i] * coeff[j];
        }
    }
    degree += p.degree;
    delete[] coeff;
    coeff = newCoeff;
    correctDegree();
    return *this;
}

ostream &operator<<(ostream &output, const Polynom &p)
{
    bool t = false; // if nothing is printed
    for (int i = p.degree; i > 0; --i)
    {
        if (p.coeff[i] != 0)
        {
            if (t)
            {
                output << (p.coeff[i] > 0 ? "+" : "");
            }
            t = true;
            if (p.coeff[i] == 1)
                output << "x";
            else
                output << p.coeff[i] << "*x";
            if (i != 1)
                output << "^" << i;
        }
    }
    output << (p.coeff[0] > 0 && t ? "+" : "") << p.coeff[0] << endl;
    return output;
}

Polynom Polynom::derivative(int deg)
{

    if (deg > degree)
        return Polynom();

    if (deg < 0)
        deg = 1;
    Polynom res(degree - deg);

    for (int i = deg; i <= degree; ++i)
    {
        res[i - deg] = coeff[i];
        for (int j = 0; j < deg; ++j)
        {
            res[i - deg] *= i - j;
        }
    }

    return res;
}

// If there are higher degrees of the variable with 0 coefficient
void Polynom::correctDegree()
{
    bool t = false;
    while (coeff[degree] == 0)
    {
        t = true;
        degree--;
    }
    if (t)
    {
        double *coeffNew = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coeffNew[i] = coeff[i];
        delete[] coeff;
        coeff = coeffNew;
    }
}

int main()
{
    double arr[] = {5}, arr2[] = {5, 5, 5, 6, 4}, arr3[] = {5, 5, -5, -6};

    // Test1 code
    /*Polynom p1(arr2, 4), p2(arr3, 3), p3(arr, 0);
    cout << p1 + p2;
    cout << p2 + p1;
    cout << p1 * p2;
    cout << p2 * p1;
    cout << p1;
    cout << p1.derivative();
    cout << p1.derivative(3);
    p1 += p2;
    cout << p3[0] << '\n'
         << p3;*/

    // Test2 code
    /*Polynom p, p1(6), p2(arr, 5), p3(p1);
    cout << "p = " << p << endl;
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << p3 << endl;
    cout << Polynom::getObjCount() << endl;
    cout << p2[3] << endl;
    p2[5] = -10;
    cout << "After modification p2 = " << p2 << endl;
    p = p1;
    cout << "p = " << p << endl;
    cout << "p1 + p2 = " << p1 + p2 << endl;
    p += p2;
    cout << "p += p2 : " << p << endl;*/
}