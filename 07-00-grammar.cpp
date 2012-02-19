#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

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

typedef std::vector<std::string> Rule;
typedef std::vector<Rule> Rule_collection;
typedef std::map<std::string, Rule_collection> Grammar;

Grammar read_grammar(std::istream& in)
{
    using namespace std;
    Grammar ret;
    string line;

    while(getline(in, line)) {
        vector<string> entry = split(line);
        if(!entry.empty())
            ret[entry[0]].push_back(
                Rule(entry.begin() + 1, entry.end())
                );
    }
    return ret;
}

bool bracketed(const std::string& s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size()-1] == '>';
}

void gen_aux(const Grammar& g, const std::string& word, 
    std::vector<std::string>& ret)
{
    if(!bracketed(word)) {
        ret.push_back(word);
    } else {
        // locate the rule that corresponds to word
        Grammar::const_iterator it = g.find(word);
        if(it == g.end())
            throw std::logic_error("empty rule");
        // fetch the set of possible rules
        const Rule_collection& c = it->second;
        // from which we select one at random
        const Rule& r = c[random() % c.size()];
        // recursivelly expand the selected rule
        for(Rule::const_iterator i = r.begin(); i != r.end(); ++i)
            gen_aux(g, *i, ret);
    }
}


std::vector<std::string> gen_sentence(const Grammar& g)
{
    using namespace std;
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}

std::string concatenate(const std::vector<std::string>& v)
{
    using namespace std;
    string ret;
    vector<string>::const_iterator it = v.begin();
    if(!v.empty()) {
        copy(it->begin(), it->end(), back_inserter(ret));
        ++it;
    }
    for(;it != v.end(); ++it) {
        ret.push_back(' ');
        copy(it->begin(), it->end(), back_inserter(ret));
    }
    return ret;
}

int main()
{
    srandom(time(NULL));
    Grammar g = read_grammar(std::cin);
    std::vector<std::string> ret = gen_sentence(g);
    std::string s = concatenate(ret);
    std::cout << s << std::endl;

    return 0;
}








