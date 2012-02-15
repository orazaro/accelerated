#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

#include <iostream>
#include <string>
#include <vector>

//#define GRADE_INPLACE

struct Student_info {
	std::string name;
#ifdef GRADE_INPLACE
	double final_grade;
#else
	double midterm, final;
	std::vector<double> homework;
#endif
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif /*GUARD_Student_info_h*/
