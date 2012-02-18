#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "grade.h"
#include "median.h"
#include "Student_info.h"

bool did_all_hw(const Student_info& s)
{
    return (
        find(s.homework.begin(), s.homework.end(), 0)
        == s.homework.end()
        );
}

double grade_aux(const Student_info& s)
{
    try {
        return grade(s);
    } catch(std::domain_error) {
        return grade(s.midterm, s.final, 0);
    }
}

double analysis(const std::vector<Student_info>& students,
    double grade_func(const Student_info&))
{
    using namespace std;
    vector<double> grades;

    transform(students.begin(), students.end(),
        back_inserter(grades), grade_func);
    return median(grades);
}


double median_analysis(const std::vector<Student_info>& students)
{
    return analysis(students, grade_aux);
}

void write_analysis(std::ostream& out, const std::string& name,
    double analysis(const std::vector<Student_info>&),
    const std::vector<Student_info>& did,
    const std::vector<Student_info>& didnt)
{
    out << name << ": median(did) - " << analysis(did) <<
        ", median(didnt) = " << analysis(didnt) << std::endl;
}

void write_analysis(std::ostream& out, const std::string& name,
    double grade_func(const Student_info&),
    const std::vector<Student_info>& did,
    const std::vector<Student_info>& didnt)
{
    out << name << ": median(did) - " << analysis(did, grade_func) <<
        ", median(didnt) = " << analysis(didnt, grade_func) << std::endl;
}

/* average analysis */
#include <numeric>
double average(const std::vector<double>& v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double average_grade(const Student_info& s)
{
    return grade(s.midterm, s.final, average(s.homework));
}
double average_analysis(const std::vector<Student_info>& students)
{
    return analysis(students, average_grade);
}
/* optimistic */
double optimistic_median(const Student_info& s)
{
    using namespace std;
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(),
        back_inserter(nonzero), 0);
    if(nonzero.empty())
        return grade(s.midterm, s.final, 0);
       else
        return grade(s.midterm, s.final, median(nonzero));
}
double optimistic_median_analysis(const std::vector<Student_info>& students)
{
    return analysis(students, optimistic_median);
}


int main()
{
    using namespace std;
    vector<Student_info> did, didnt;

    // read all students, separating them based on whether all homework was done
    Student_info student;
    while(read(cin, student)) {
        if(did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }
    
    if(did.empty()) {
        cout << "No student did all the homework!" << endl;
        return 1;
    }
    if(didnt.empty()) {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }

    // do the analysis with more generalized form
    write_analysis(cout, "median", grade_aux, did, didnt);
    // do the analysis with less generalized form
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

    return 0;
}

