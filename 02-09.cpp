#include <iostream>

int main()
{
	std::cout << "Please, enter two numbers: ";
	int i1, i2;
	std::cin >> i1 >> i2;

	std::string op = "=";
	if(i1 > i2)
		op = ">";
	else if(i2 > i1)
		op = "<";

	std::cout << i1 << " " << op << " " << i2 << std::endl;

	return 0;
}
