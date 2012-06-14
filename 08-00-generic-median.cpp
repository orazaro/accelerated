#include <iostream>
#include <vector>
#include <stdexcept>
#include <numeric>

using namespace std;

template<class T>
T median(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;

    vec_sz size = v.size();
    if( size == 0)
        throw domain_error("median of an empty vector");
    sort(v.begin(),v.end());
    vec_sz mid = size / 2;
    return size % 2 == 0 ? (v[mid] + v[mid-1]) / 2 : v[mid];
}

template<class T>
T tmax(const T& left, const T& right)
{
    return left > right ? left : right;
}

int main()
{
    int n = 1000;
    vector<double> v(n,0);

    for(int i = 0; i < n; i++)
        v[i] = random() % n;

    double med = median(v);
    double av = accumulate(v.begin(),v.end(), 0.0) / n;

    for(int i = 0; i < n; i++)
        cout << v[i] << " ";

    cout << endl;
    cout << "median=" << med << " av=" << av<< endl;
    cout << "max(median,av) = " << tmax(med,av) << endl;

    return 0;
}
