#include <iostream>
#include <cctype>

int main()
{
    std::string s;
    while(getline(std::cin, s)) {
        for(std::string::iterator it = s.begin();
            it != s.end(); ++it) 
            *it = toupper(*it);
        std::cout << s << std::endl;
    }
    return 0;
}
