#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    using namespace std;
    string s;
    map<string, int> counters;
    
    while(cin >> s)
        ++counters[s];

    typedef map<int, vector<string> > Ranges;
    Ranges r;
    for(map<string, int>::const_iterator it = counters.begin();
        it != counters.end(); ++it) {
        r[it->second].push_back(it->first);
    }
    for(Ranges::const_iterator it = r.begin();
        it != r.end(); ++it) {
        cout << it->first << ":";
        for(vector<string>::const_iterator i = it->second.begin();
            i != it->second.end(); ++i) {
            cout << " " << *i;
        }
        cout << endl;
    }
    return 0;
}
