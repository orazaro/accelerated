#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <map>

#include "grade.h"
#include "Student_info.h"

const std::string grade_range(const Student_info& s)
{
    double g = grade(s);
    if(g < 60) return std::string("F");
    else if(g < 70) return std::string("D");
    else if(g < 80) return std::string("C");
    else if(g < 90) return std::string("B");
    else if(g <=  100) return std::string("A");
    else throw std::domain_error("student grade > 100");
}

int main(int argc, char* argv[])
{
    using namespace std;
    StudentList students;
    read(std::cin, students);
   
    typedef map<string, vector<string> > Ranges;
    Ranges m;

    for(StudentList::const_iterator it = students.begin();
        it != students.end(); ++it) {
        m[grade_range(*it)].push_back(it->name);
        cout << it->name << " " << grade(*it) 
            << " " << grade_range(*it) << endl;
    }
    cout << string(10,'-') << endl;
    
    for(Ranges::const_iterator it = m.begin();
        it != m.end(); ++it) {
        const vector<string>& s = it->second;
        cout << it->first << "(" << s.size() << "):";
        for(vector<string>::const_iterator i = s.begin();
            i != s.end(); ++i)
            cout << " " << *i;
        cout << endl;
    }
    return 0;
}

