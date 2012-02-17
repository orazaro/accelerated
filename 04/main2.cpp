#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "grade.h"
#include "Student_info.h"

int main()
{
    std::vector<Student_info> students;
    Student_info record;
    std::string::size_type maxlen = 0;

    // read and store the records, and find the length of the longest name
    while(read(std::cin, record)) {
        maxlen = std::max(maxlen, record.name.size());
        students.push_back(record);
    }

    std::sort(students.begin(), students.end(), compare);
    
    for( std::vector<Student_info>::size_type i = 0;
        i != students.size(); ++i) {
        // write the name, padded on the right to maxlen+1 characters
        std::cout << students[i].name
            << std::string(maxlen + 1 - students[i].name.size(),' ');
        // compute and write the grade
        try {
            double final_grade = grade(students[i]);
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade 
                << std::setprecision(prec);
        } catch (std::domain_error e) {
            std::cout << e.what();
        }
        std::cout << std::endl;
    }
    return 0;
}

