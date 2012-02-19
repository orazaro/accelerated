#include <iostream>
#include <map>

int main()
{
    using namespace std;
    string s;
    map<string, int> counters;
    
    while(cin >> s)
        ++counters[s];

    for(map<string, int>::const_iterator it = counters.begin();
        it != counters.end(); ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
    return 0;
}
