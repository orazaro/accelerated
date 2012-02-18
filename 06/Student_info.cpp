#include "Student_info.h"
#include "grade.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <stdexcept>


bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

std::istream& read(std::istream& in, Student_info& s)
{
    in >> s.name;
    if(!in) return in;

    in >> s.midterm >> s.final;
    read_hw(in, s.homework);

    s.final_grade = grade(s.midterm, s.final, s.homework);

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

std::istream& read(std::istream& in, std::vector<Student_info>& students)
{
    Student_info record;

    // read and store the records, and find the length of the longest name
    while(read(in, record)) {
        students.push_back(record);
    }
    std::sort(students.begin(), students.end(), compare);
    return in;
}

std::istream& read(std::istream& in, std::list<Student_info>& students)
{
    Student_info record;

    // read and store the records, and find the length of the longest name
    while(read(in, record)) {
        students.push_back(record);
    }
    students.sort(compare);
    return in;
}

void out_students(const StudentList& students, std::ostream& out)
{
    std::string::size_type maxlen = 0;
    
    // calc maxlen
    for( StudentList::const_iterator iter = students.begin();
        iter != students.end(); ++iter) {
        maxlen = std::max(maxlen, iter->name.size());
    }
    // out
    for( StudentList::const_iterator iter = students.begin();
        iter != students.end(); ++iter) {
        // write the name, padded on the right to maxlen+1 characters
        out << iter->name
            << std::string(maxlen + 1 - iter->name.size(),' ');
        // compute and write the grade
        try {
            double final_grade = grade(*iter);
            std::streamsize prec = std::cout.precision();
            out << std::setprecision(3) << final_grade 
                << std::setprecision(prec);
        } catch (std::domain_error e) {
            out << e.what();
        }
        out << std::endl;
    }
}

StudentList extract_fails_container(StudentList& students)
{
    StudentList fail;
    StudentList::iterator iter = students.begin();
    while(iter != students.end()) {
        if(fgrade(*iter)) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        }
        else
            ++iter;
    }
    return fail;
}

std::vector<Student_info>
extract_fails_resize(std::vector<Student_info>& students)
{
    StudentList fail;
    StudentList::iterator iter = students.begin(), pass = iter;
    StudentList::size_type passed = 0;
    while(iter != students.end()) {
        if(fgrade(*iter)) {
            ++iter;
        }
        else {
            if(pass == iter) {
                ++iter; ++pass;
            } else {
                Student_info s = *pass;
                *pass = *iter; ++pass;
                *iter = s;
            }
            passed++;
        }
    }
    for(StudentList::size_type i = passed; i != students.size(); ++i)
            fail.push_back(students[i]);
    students.resize(passed);
    return fail;
}

static bool pgrade(const Student_info& s)
{
    return !fgrade(s);
}

std::vector<Student_info>
extract_fails_remove(std::vector<Student_info>& students)
{
    std::vector<Student_info> fail;
    remove_copy_if(students.begin(), students.end(),
        back_inserter(fail), pgrade);
    students.erase(
        remove_if(students.begin(), students.end(), fgrade),
        students.end()
        );
    return fail;

}
