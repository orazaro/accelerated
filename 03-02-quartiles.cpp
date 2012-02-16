#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cout << "Enter all your homework grades, \n"
        "followed by end-of-file: ";

    double x;
    vector<double> homework;

    // invariant: homework contains all the homework grades read so far
    while( cin >> x ) {
        homework.push_back(x);
    }

    typedef vector<double>::size_type vec_sz;
    vec_sz size = homework.size();
    if(size == 0) {
        cout << endl << "You must enter your grades. "
            "Please try again." << endl;
        return 1;
    }
    
    sort(homework.begin(), homework.end());

    int i2 = (int) ( size / 2 );
    int i1 = (int) ( (0 + i2) / 2 );
    int i3 = (int) ( (i2 + size) / 2);

    cout << "Quartiles:" << endl;
    for(int i = 0; i < i1; i++)
        cout << homework[i] << ' ';
    cout << endl;
    for(int i = i1; i < i2; i++)
        cout << homework[i] << ' ';
    cout << endl;
    for(int i = i2; i < i3; i++)
        cout << homework[i] << ' ';
    cout << endl;
    for(int i = i3; i < (int)size; i++)
        cout << homework[i] << ' ';
    cout << endl;


    return 0;
}
