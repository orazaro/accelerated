// use of rbegin() as reverse iterator
#include <iostream>
#include <string>

int main()
{
    typedef std::string::const_reverse_iterator iter;
    std::string word;
    while(std::cin >> word) {
        for(iter r = word.rbegin(); r != word.rend(); r++)
            std::cout << *r;
        std::cout << std::endl;
    }
    return 0;
}
