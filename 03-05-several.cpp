#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> students;
    vector<double> grades;

    while(1) {
        cout << "Please, enter your name or end: ";
        string name;
        cin >> name;
        if( name == "end" ) break;
        cout << "Hello, " << name << "!" << endl;

        cout << "Please enter your midterm and final exam grades: ";
        double midterm, final;
        cin >> midterm >> final;
    
        int ngrades = 3;
        cout << "Enter "<< ngrades << " your homework grades: ";

        int count = 0;
        double sum = 0;
        double x;
        for(int i = 0; i < ngrades && cin >> x; i++) {
            ++count;
            sum += x;
        }

        double grade = 0.2 * midterm + 0.4 * final + 0.4 * sum / count;
        students.push_back(name);
        grades.push_back(grade);
    }

    cout << endl << "Students:" << endl;
    for(int i = 0; i < (int)students.size(); i++)
    {
        cout << students[i] << " " << grades[i] << endl;
    }

    return 0;
}
