#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <sstream>


bool not_url_char(char c)
{
    static const std::string url_ch = "~;/?:@=&$-_.+!*'(),";
    return !( 
        isalnum(c) ||
        find(url_ch.begin(), url_ch.end(), c) != url_ch.end()
        );
}

std::string::const_iterator
url_beg_book(std::string::const_iterator b, std::string::const_iterator e)
{
    using namespace std;
    static const string sep = "://";
    typedef string::const_iterator iter;

    iter i = b;
    while((i = search(i, e, sep.begin(), sep.end())) != e) {
        //make sure the separator isn't at the beginning or end of the line
        if(i != b && i + sep.size() != e) {
            iter beg = i;
            while(beg != b && isalpha(beg[-1]))
                --beg;
            // is there at least one appropriate character 
            // before and after the separator?
            if(beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }
        i += sep.size();
    }
    return e;
}

std::string::const_iterator
url_end(std::string::const_iterator b, std::string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

std::vector<std::string> find_urls(const std::string& s)
{    
    using namespace std;
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();

    // look through the entire input
    while(b != e) {
        // look for one or more letters followed by ://
        b = url_beg_book(b, e);
        // if we found it
        if(b != e) {
            // get the rest of the URL
            iter after = url_end(b, e);

            ret.push_back(string(b, after));
            b = after;
        }
    }

    return ret;
}


typedef std::map<std::string, std::vector<int> > Xref;

Xref xref(std::istream& in, 
    std::vector<std::string> find_words(const std::string&) = find_urls)
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
