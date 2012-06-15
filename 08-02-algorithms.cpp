#include <iostream>
#include <stdexcept>
#include <list>

using namespace std;

template < typename Iter >
bool my_equal(Iter b, Iter e, Iter d)
{
    try 
    {
        while( b != e ) {
            if(*b != *d)
                return false;
            ++b; ++d;
        }
    }
    catch (domain_error& e) 
    {
        return false;
    };

    return true;
}

int main()
{
    list<string> w;
    w.push_back("abc");
    w.push_back("two");
    w.push_back("baby");

    list<string> w2 = w;

    cout << "equal[" << *w.begin() << "," << *w2.begin() << "] " 
        << my_equal(w.begin(), w.end(), w2.begin()) << endl;

    w.pop_back();
    cout << "equal2 " << my_equal(w2.begin(), w2.end(), w.begin()) << endl;

    return 0;
}
