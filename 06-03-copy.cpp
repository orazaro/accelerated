#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    using namespace std;
    vector<int> u(10,100);
    vector<int> v;
#if 1
    copy(u.begin(), u.end(), back_inserter(v));
#else 
    {
    v.resize(u.size());
    vector<int>::iterator it = v.begin();
    copy(u.begin(), u.end(), it);
    }
#endif
    
    vector<int>::const_iterator it = v.begin();
    cout << "sum(" << *it++;
    for(; it < v.end(); ++it)
        cout << "+" << *it;
    cout << ")=" << accumulate(v.begin(), v.end(), 0) << endl; 

    return 0;
}
