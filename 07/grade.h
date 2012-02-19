#ifndef GUARD_grade_h
#define GUARD_grade_h

#include <vector>
#include "Student_info.h"

double grade(double midterm, double final, double homework);
double grade(double midterm, double final, const std::vector<double>& hw);
double grade(const Student_info& s);
bool fgrade(const Student_info& s);
bool mygrade(const Student_info& s);

#endif /*GUARD_grade_h*/
