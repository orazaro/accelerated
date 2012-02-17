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

bool did_all_hw(const Student_info& s)
{
    return (
        find(s.homework.begin(), s.homework.end(), 0)
        == s.homework.end()
        );
}

int main()
{
    using namespace std;
    vector<Student_info> did, didnt;
    Student_info student;

    // read all students, separating them based on whether all homework was done
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

    return 0;
}

