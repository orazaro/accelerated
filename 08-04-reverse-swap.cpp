#include <iostream>
#include <string>

using namespace std;

template<class Bi>
void swap2(Bi& b, Bi& e)
{
    Bi t(b);
    b = e;
    e = t;
}

template<class Bi> void my_reverse(Bi begin, Bi end)
{
    while( begin != end ) {
        --end;
        if( begin != end ) {
            swap2(*begin++, *end);
        }
    }
}

int main()
{
    string s1("123456"), s2 = s1;
    my_reverse(s2.begin(), s2.end());

    cout << "s1=" << s1 << " s2=" << s2 << endl;
    
    return 0;
}
