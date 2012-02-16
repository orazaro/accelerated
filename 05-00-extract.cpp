#include <iostream>
#include <vector>
#include <string>

std::vector<int> extract_odd(std::vector<int>& vec)
{
    std::vector<int> odd, even;
    for(std::vector<int>::size_type i = 0;
        i != vec.size(); ++i)
        if( vec[i] % 2 == 0 )
            even.push_back(vec[i]);
        else
            odd.push_back(vec[i]);
    
    vec = even;
    return odd;
}

void out_vec(const std::vector<int>& vec, const std::string title)
{
    std::cout << title;
    for(std::vector<int>::size_type i = 0;
        i != vec.size(); ++i)
        std::cout << " " << vec[i];
}

int main()
{
    std::vector<int> vec;
    
    for(int x; std::cin >> x;)
        vec.push_back(x);
    
    std::vector<int> odd = extract_odd(vec);
    out_vec(odd,"odd"); std::cout << std::endl;
    out_vec(vec,"even"); std::cout << std::endl;

    return 0;
}
