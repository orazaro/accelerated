#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    typedef std::string::const_iterator citer;
    typedef std::string::iterator iter;
    string::size_type maxlen = 0;
    std::string best, ascenders("bdfhklt"), descenders("gjpqy");

    std::string word;
    while(std::cin >> word) {
        string t;
        for(iter i = word.begin(); i != word.end(); ++i) {
            char c = *i = tolower(*i);
            if(string::npos != ascenders.find_first_of(c))
                t += "a";
            if(string::npos != descenders.find_first_of(c))
                t += "d";
        }
        if(!t.size()){
            if(word.size() > maxlen) {
                maxlen = word.size();
                best = word;
            }
        }
        //std::cout << word << "\t" << t << endl;
    }
    std::cout << "the best: " << best << std::endl;
    return 0;
}
