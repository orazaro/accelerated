#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>

std::vector<std::string> split(const std::string& s)
{    
    std::vector<std::string> vec; 
    std::string::const_iterator i = s.begin();
    while(i != s.end())
    {
        while(i != s.end() && isspace(*i))
            ++i; 
        std::string::const_iterator j = i;
        while(j != s.end() && !isspace(*j))
            ++j;
        if(j != i) {
            std::string token = std::string(i, j);
            vec.push_back(token);
            i = j;
        }
    }

    return vec;
}

int main() {
    std::string s;
    while(std::getline(std::cin, s)) {
        std::vector<std::string> v = split(s);
        for(std::vector<std::string>::size_type i = 0; i != v.size(); ++i)
            std::cout << "[" << v[i] << "]" << std::endl;
    }
    return 0;
}
