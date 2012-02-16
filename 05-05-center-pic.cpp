#include <iostream>
#include <string>
#include <vector>

using namespace std;

void out(const std::vector<std::string>& v)
{
    for(std::vector<std::string>::const_iterator iter = v.begin();
        iter != v.end(); ++iter)
        cout << *iter << endl;
}

std::string::size_type width(const std::vector<std::string>& v)
{
    string::size_type maxlen = 0;
    for(std::vector<std::string>::const_iterator iter = v.begin();
        iter != v.end(); ++iter)
        maxlen = max(maxlen, iter->size());
    return maxlen;
}

std::vector<std::string> center(const std::vector<std::string>& v)
{
    vector<string> ret;
    string::size_type maxlen = 80;
    for(std::vector<std::string>::const_iterator iter = v.begin();
        iter != v.end(); ++iter) {
        string::size_type len = (maxlen - iter->size()) / 2;
        ret.push_back(string(len,' ') + (*iter) + string(len,' '));
    }
    return ret;
}

int main()
{
    // read data
    vector<string> v,f;
    string line;
    while(getline(cin, line))
        v.push_back(line);
    f = center(v);
    out(f);
}
