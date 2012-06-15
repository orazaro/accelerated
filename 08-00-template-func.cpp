#include <iostream>

using namespace std;

double sum(double x, double y)
{
    return x + y;
}
double mul(double x, double y)
{
    return x * y;
}
double div(double x, double y)
{
    return x / y;
}

template < double Op(double,double) >
double make(double x, double y)
{
    return Op(x,y);
}

int main()
{
    cout << "sum:" << make<sum>(3,5) << endl;
    cout << "mul:" << make<mul>(3,5) << endl;
    cout << "div:" << make<div>(3,5) << endl;

    return 0;
}
