#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    typedef std::string::const_iterator iter;
    std::string word;
    std::string::size_type maxlen = 0;
    std::string poly;
    while(std::cin >> word) {
        if( equal(word.begin(), word.end(), word.rbegin()) ) {
            if(word.size() > maxlen) {
                maxlen = word.size();
                poly = word;
            }
        }
    }
    std::cout << "palindrom: " << poly << std::endl;
    return 0;
}
