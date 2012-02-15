#include <vector>
#include <iostream>

std::vector<double>& f()
{
	std::vector<double> *v = new std::vector<double>;
	v->push_back(1);
	v->push_back(2);
	return *v;
}

int main()
{
	int n = 1;
	double d = f()[n];
	std::cout << d << std::endl;
}
