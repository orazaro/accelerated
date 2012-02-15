#include <iostream>
#include <iomanip>

using std::setw;

int main()
{
	for(int i = 0; i <= 100; ++i) {
		std::cout << setw(3) << i << setw(6) << i*i << std::endl;
	}
}
