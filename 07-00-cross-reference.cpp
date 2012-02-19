#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

// isspace is overloaded so we use wrapper function as argument for find_if
inline bool space(char c)
{
    return isspace(c);
}
inline bool not_space(char c)
{
    return !isspace(c);
}

std::vector<std::string> split(const std::string& str)
{    
    typedef std::string::const_iterator iter;
    std::vector<std::string> ret;

    iter i = str.begin();
    while(i != str.end())
    {
        // ignore leading spaces
        i = find_if(i, str.end(), not_space);
        // find end of next word
        iter j = find_if(i, str.end(), space);
        if(i != str.end())
            ret.push_back(std::string(i, j));
        i = j;
    }
    return ret;
}

std::map<std::string, std::vector<int> >
xref(std::istream& in, 
    std::vector<std::string> find_words(const std::string&) = split)
{
    using namespace std;
    string line;
    int line_number = 0;
    map<string, vector<int> > ret;

    while(getline(in, line)) {
        ++line_number;
        vector<string> words = find_words(line);
        for(vector<string>::const_iterator it = words.begin();
            it != words.end(); ++it)
            ret[*it].push_back(line_number);
    }
    return ret;
}

int main()
{
    using namespace std;
    map<string, vector<int> > ret = xref(cin);

    // write results
    for(map<string, vector<int> >::const_iterator it = ret.begin();
        it != ret.end(); ++it) {
        cout << it->first << " occurs on line(s): ";
        vector<int>::const_iterator line_it = it->second.begin();
        cout << *line_it; ++line_it;
        while(line_it != it->second.end()) {
            cout << ", " << *line_it;
            ++line_it;
        }
        cout << endl;
    }

    return 0;
}
