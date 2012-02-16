#include <iostream>

using std::cout;
using std::endl;
using std::cin;


int main()
{
    const int width = 10;
    const int height = 4;

    cout << "square" << endl;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < height; ++j)
            cout << '*';
        cout << endl;
    }
    cout << "rectangle" << endl;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j)
            cout << '*';
        cout << endl;
    }
    cout << "triangle" << endl;
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j <= i; ++j)
            cout << '*';
        cout << endl;
    }

    int i = 0;
    while (i < 10) {
            i += 1;
            std::cout << i << std::endl;
    }

    return 0;
}
