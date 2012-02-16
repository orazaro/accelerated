#include <iostream>
#include <iomanip>

using std::setw;

int main()
{
    int n = 99;
    int w1 = 0;

    for(int m = n+1; m > 0; m = m / 10)
        w1++;

    int w2 = w1 << 1;

    for(int i = 0; i < n; ++i) {
        std::cout << setw(w1) << i << setw(w2) << i*i << std::endl;
    }
}
