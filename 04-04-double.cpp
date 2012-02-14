#include <iostream>
#include <iomanip>

using std::setw;
using std::setprecision;
using std::fixed;

int main()
{
	double xmin = 0;
	double xmax = 9.9;
	double dx = 0.1;

	int w1 = 4, w2 = w1 * 2;

	for(double x = xmin; x < xmax; x+=dx) {
		std::cout << setprecision(3) << fixed
			<< setw(w1) << x << setw(w2) << x*x << std::endl;
	}
}
