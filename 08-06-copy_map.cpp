#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <list>

using namespace std;


int main()
{
    map<int, string> m;
    list<pair<const int, string> > x;
    typedef list<pair<const int, string> > LP;

    m[1] = "one";
    m[2] = "two";

    copy(m.begin(), m.end(), back_inserter(x)); 
    for(LP::const_iterator it = x.begin(); it != x.end(); ++it)
        cout << it->first << ":" << it->second << endl;
    
    return 0;
}
