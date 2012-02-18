#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

#include <iostream>
#include <string>
#include <vector>
#include <list>

struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
    double final_grade;
};

typedef std::vector<Student_info> StudentList;
//typedef std::list<Student_info> StudentList;

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);
std::istream& read(std::istream& in, std::vector<Student_info>& students);
std::istream& read(std::istream& in, std::list<Student_info>& students);
void out_students(const StudentList& students, std::ostream& out);

StudentList extract_fails_container(StudentList& students);
std::vector<Student_info> 
extract_fails_resize(std::vector<Student_info>& students);
std::vector<Student_info>
extract_fails_remove(std::vector<Student_info>& students);
std::vector<Student_info>
extract_fails_partition(std::vector<Student_info>& students);

#endif /*GUARD_Student_info_h*/
