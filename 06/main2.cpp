#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "grade.h"
#include "Student_info.h"

std::vector<Student_info> (*extract_fails[])(std::vector<Student_info>&) =
{   
    extract_fails_container,
    extract_fails_resize,
    extract_fails_remove,
    extract_fails_partition,
    extract_fails_my,
};

int main(int argc, char* argv[])
{
    int prog_max = sizeof(extract_fails)/sizeof(int(*)()),
        prog = prog_max -1;
    if(argc > 1) prog = (unsigned)atoi(argv[1]) % prog_max ;

    StudentList students;
    read(std::cin, students);

    StudentList fail = extract_fails[prog](students);

    std::cout << "pass:" << std::endl;
    out_students(students, std::cout);
    std::cout << "fail:" << std::endl;
    out_students(fail, std::cout);
    
    return 0;
}

