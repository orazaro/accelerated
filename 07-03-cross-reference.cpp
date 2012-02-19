#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <sstream>

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

typedef std::map<std::string, std::vector<int> > Xref;


Xref xref(std::istream& in, 
    std::vector<std::string> find_words(const std::string&) = split)
{
    using namespace std;
    string line;
    int line_number = 0;
    Xref ret;

    while(getline(in, line)) {
        ++line_number;
        vector<string> words = find_words(line);
        for(vector<string>::const_iterator it = words.begin();
            it != words.end(); ++it) {
            vector<int>& lines = ret[*it];
            if(find(lines.begin(), lines.end(), line_number) == lines.end())
                lines.push_back(line_number);
        }
    }
    return ret;
}

int main()
{
    using namespace std;
    Xref ret = xref(cin);

    // write results
    for(Xref::const_iterator it = ret.begin();
        it != ret.end(); ++it) {
        stringstream ss; 
        pair<const string, vector<int> > p = *it;
        ss << p.first << " : ";
        vector<int>::const_iterator line_it = p.second.begin();
        ss << *line_it; ++line_it;
        while(line_it != p.second.end()) {
            ss << ", "; ss << *line_it;
            ++line_it;
        }
        string out = ss.str();
        if(out.size() >= 77) {out.resize(76); out+="...";}
        cout << out << endl;
    }

    return 0;
}
