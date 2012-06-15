#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <list>

using namespace std;

template <typename X, typename Y>
X max(X x, Y y)
{
    X z = X(y);
    if( x > z )
        return x;
    else
        return z;
}


int main()
{
    int x = 1;
    double y = 1.123;

    cout << "max of " << x << " and " << y << " is " << max(x,y) << endl;
    
    return 0;
}
