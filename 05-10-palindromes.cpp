#include <iostream>
#include <string>
#include <cctype>

int main()
{
	typedef std::string::const_iterator iter;
	std::string word;
	int maxlen = 0;
	std::string poly;
	while(std::cin >> word) {
		int s = (int)word.size();
		if(s < 2) continue;
		int l = 0, r = s - 1;
		while( l < r && tolower(word[l]) == tolower(word[r]) ) {
			 ++l; --r;
		}
		if(l >= r){
			if(s > maxlen) {
				maxlen = s;
				poly = word;
			}
		}
	}
	std::cout << "palindrom: " << poly << std::endl;
	return 0;
}
