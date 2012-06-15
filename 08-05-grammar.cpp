/*  generate sentences using BNF grammar from input
    (without recursive calls)
*/
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iterator>

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

// return a random integer in the range [0, n)
int nrand(int n)
{
    if(n <= 0 || n > RAND_MAX)
        throw std::domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;
    do r = random() / bucket_size;
    while(r >= n);
    return r;
}

template <typename Out>
void gen_sentence(const Grammar& g, Out out)
{
    using namespace std;
    list<string> stack;
    stack.push_back("<sentence>");
    while(!stack.empty()) {
        string word = stack.back(); stack.pop_back();
        if(!bracketed(word)) {
            *out++ = word;
        } else {
            // locate the rule that corresponds to word
            Grammar::const_iterator it = g.find(word);
            if(it == g.end())
                throw std::logic_error("empty rule");
            // fetch the set of possible rules
            const Rule_collection& c = it->second;
            // from which we select one at random
            const Rule& r = c[nrand(c.size())];
            // expand the selected rule
            for(Rule::const_reverse_iterator i = r.rbegin(); 
                i != r.rend(); ++i)
                stack.push_back(*i);
        }
    }
}

template < class Iter >
std::string concatenate(Iter b, Iter e)
{
    using namespace std;
    string ret;
    if(b != e) {
        copy(b->begin(), b->end(), back_inserter(ret));
        ++b;
    }
    for(;b != e; ++b) {
        ret.push_back(' ');
        copy(b->begin(), b->end(), back_inserter(ret));
    }
    return ret;
}

int main()
{
    srandom(time(NULL));
    Grammar g = read_grammar(std::cin);
    std::cout << "list" << std::endl;
    for(int i = 0; i < 2; ++i) {
        std::list<std::string> ret;
        gen_sentence(g, back_inserter(ret));
        std::string s = concatenate(ret.begin(), ret.end());
        std::cout << s << std::endl;
    }

    std::cout << "vector" << std::endl;
    for(int i = 0; i < 2; ++i) {
        std::vector<std::string> ret;
        gen_sentence(g, back_inserter(ret));
        std::string s = concatenate(ret.begin(), ret.end());
        std::cout << s << std::endl;
    }

    std::cout << "direct output" << std::endl;
    for(int i = 0; i < 2; ++i) {
        gen_sentence(g, std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

