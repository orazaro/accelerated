#include <iostream>
#include <vector>
#include <string>

struct WordCount {
	std::string word;
	int count;
};

typedef std::vector<WordCount>::size_type vec_sz;

int read(std::istream& in, std::vector<WordCount>& vec)
{
	std::string word;
	int words = 0;
	while(in >> word) {
		words++;
		bool found = false;
		for(vec_sz i = 0; i != vec.size(); ++i)
			if(vec[i].word == word) {
				vec[i].count ++;
				found = true;
				break;
			}
		if(!found) {
			WordCount wc = {word,1};
			vec.push_back(wc);
		}
	}
	return words;
}


int main()
{
	std::vector<WordCount> vec;
	int words = read(std::cin, vec);
	std::cout << "Result:" << std::endl;
	for(vec_sz i = 0; i != vec.size(); ++i)
		std::cout << vec[i].word << " " << vec[i].count << std::endl;
	std::cout << "sum=" << words << std::endl;

	return 0;
}
