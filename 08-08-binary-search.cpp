#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

template<class Ran, class X>
bool my_binary_search(Ran begin, Ran end, const X& x)
{
    while (begin < end) {
        // find the midpoint of the range
        Ran mid = begin + (end - begin) / 2;
        // see which part of the range contains x; keep looking only in that part 
        if (x < *mid)
            end = mid;
        else if (*mid < x)
            begin = mid + 1;
        // if we got here, then *mid == x so we're done 
        else return true;
    }
    return false;
}

int main()
{
    double a[] = {1.1, 2.21, 3, 4, 5.5, 10.4};
    vector<double> v(a, a+sizeof(a)/sizeof(*a));

    copy(v.begin(), v.end(), ostream_iterator<double>(cout, " "));
    cout << endl;

    double x = 3;
    cout << x << " search " << my_binary_search(v.begin(), v.end(), x) << endl;
    x = 3.1;
    cout << x << " search " << my_binary_search(v.begin(), v.end(), x) << endl;
    
    return 0;
}
