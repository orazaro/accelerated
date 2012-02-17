#include <iostream>
#include <ctime>
#include <cstdlib>

int main(int argc, char* argv[])
{
    long n = 100;
    int m = 16;
    if(argc > 1) n = atol(argv[1]);
    srandom(time(NULL));
    while(n--) {
        std::cout << "u" << random();
        for(int i = 0; i < m; ++i)
            std::cout << " " << random()%100;
        std::cout << std::endl;
    }
    return 0;
}
