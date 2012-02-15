#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "grade.h"
#include "Student_info.h"

int main()
{
	StudentList students;

	read(std::cin, students);

	StudentList fail = extract_fails(students);

	std::cout << "pass:" << std::endl;
	out_students(students, std::cout);
	std::cout << "fail:" << std::endl;
	out_students(fail, std::cout);
	
	return 0;
}

