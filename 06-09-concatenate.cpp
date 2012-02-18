/* Use a library algorithm to concatenate all the elements of a vector<string>.*/
#include <iostream>
#include <string>
#include <vector>

int main()
{
    using namespace std;
    vector<string> v;
    string word;
    while(cin >> word)
        v.push_back(word);
    
    string sum;
    for(vector<string>::const_iterator it = v.begin();
        it != v.end(); ++it) {
        copy(it->begin(), it->end(), back_inserter(sum));
    }

    cout << "sum=" << sum << endl;
    return 0;
}
