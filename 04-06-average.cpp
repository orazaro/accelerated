#include <iostream>
#include <vector>


int main()
{	
	typedef std::vector<double>::size_type vec_sz;
	std::vector<double> vec;
	for(double x; std::cin >> x;)
		vec.push_back(x);
	double sum = 0;
	for(vec_sz i = 0; i < vec.size(); ++i)
		sum += vec[i];

	std::cout 
		<< "average="
		<< sum / vec.size()
		<< std::endl;
		
	return 0;
}
