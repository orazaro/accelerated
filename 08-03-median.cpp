#include <iostream>
#include <vector>
#include <stdexcept>
#include <numeric>
#include <iterator>

using namespace std;

template <class T, class It>
T median(It b, It e)
{
    size_t size = e - b;
    if( size == 0)
        throw domain_error("median of an empty vector");
    sort(b,e);
    size_t mid = size / 2;
    return size % 2 == 0 ? (b[mid] + b[mid-1]) / 2 : b[mid];
}

int main()
{
    int n = 100;
    vector<double> v(n,0);

    for(int i = 0; i < n; i++)
        v[i] = random() % n;

    double med = median<double>(v.begin(), v.end());
    double av = accumulate(v.begin(),v.end(), 0.0) / n;

    copy(v.begin(), v.end(), ostream_iterator<double>(cout, " "));

    cout << endl;
    cout << "median=" << med << " av=" << av<< endl;

    return 0;
}
