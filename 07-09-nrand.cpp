/* 07-09: nrand if n > RAND_MAX
to test we imitate that this case with trandom() */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <cmath>

const int TRAND_MAX = 1000;
int trandom()
{
    return random() % TRAND_MAX;
}

// return a random integer in the range [0, n)
int nrand(int n)
{
    if(n <= 0)
        throw std::domain_error("Argument to nrand is out of range");
    int result = 0;
    if(n > TRAND_MAX) {
        int parts = n / TRAND_MAX;
        for(int i = 0; i < parts; ++i)
            result += trandom();
    }
    int m = n % TRAND_MAX;
    const int bucket_size = TRAND_MAX / m;
    int r;
    do r = trandom() / bucket_size;
    while(r >= m);
    return result + r;
}

int main()
{
    using namespace std;
    const int n_gist = 10;
    vector<int> gist(n_gist);
    srandom(time(NULL));
    
    for(int i = 0; i < 1000000; ++i)
    {
        int r = nrand(99999);
        gist[r % n_gist]++;
    } 
    // check
    double mean = accumulate(gist.begin(), gist.end(), 0.0) / n_gist;
    for(int i = 0; i < n_gist; ++i) {
        double dx = mean - gist[i];
        double dx2 = sqrt(dx * dx);
        std::cout << i 
            << "\t" << gist[i] 
            << "\t" << dx2
            << " (" << sqrt(gist[i]) << ")"
            << std::endl;
    }
    return 0;
}
