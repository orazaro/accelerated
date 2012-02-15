#include "Student_info.h"
#include "grade.h"
#include <iostream>

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

std::istream& read(std::istream& in, Student_info& s)
{
	in >> s.name;
	if(!in) return in;
#ifdef GRADE_INPLACE
	double midterm,final;
	std::vector<double> homework;
	in >> midterm >> final;
	read_hw(in, homework);
	//double grade(double midterm, double final, const std::vector<double>& hw);
	s.final_grade = grade(midterm, final, homework);
#else
	in >> s.midterm >> s.final;
	read_hw(in, s.homework);
#endif
	return in;
}

std::istream& read_hw(std::istream& in, std::vector<double>& hw)
{
	if(in) {
		// reset vector
		hw.clear();
		double x;
		while( in >> x )
			hw.push_back(x);
		// clear failure flag for istream
		in.clear();
	}
	return in;
}
