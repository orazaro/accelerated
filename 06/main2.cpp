#include <iostream>
#include <algorithm>

#include "grade.h"
#include "Student_info.h"

std::vector<Student_info> (*extract_fails[])(std::vector<Student_info>&) =
{   
    extract_fails_container,
    extract_fails_resize,
    extract_fails_remove,
    extract_fails_partition
};

int main()
{
    StudentList students;

    read(std::cin, students);

    StudentList fail = extract_fails[3](students);

    std::cout << "pass:" << std::endl;
    out_students(students, std::cout);
    std::cout << "fail:" << std::endl;
    out_students(fail, std::cout);
    
    return 0;
}

