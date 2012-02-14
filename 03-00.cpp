#include <iostream>
#include <iomanip>
#include <ios>
#include <string>

using namespace std;

int main()
{
	cout << "Please, enter your name: ";
	string name;
	cin >> name;
	cout << "Hello, " << name << "!" << endl;

	cout << "Please enter your midterm and final exam grades: ";
	double midterm, final;
	cin >> midterm >> final;

	cout << "Enter all your homework grades, "
		"followed by end-of-file: ";

	int count = 0;
	double sum = 0;
	double x;
	while( cin >> x ) {
		++count;
		sum += x;
	}

	double final_grade = 0.2 * midterm + 0.4 * final;
	if(count > 0) {
		final_grade += 0.4 * sum / count;
	} else {
		cerr << "Bad data in input" << endl;
		return 1;
	}

	streamsize prec = cout.precision();
	cout << "Your final grade is " << setprecision(3)
		<< final_grade
		<< setprecision(prec) << endl;
	cout << "Precision was " << prec << endl;

	return 0;
}
