#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<string> words;
	vector<int> counts;
	
	for(string word; cin >> word; )
	{
		bool found = false;
		int size = (int) words.size();
		for(int i = 0; i < size; i++)
		{
			if(words[i] == word) {
				counts[i]++; 
				found = true;
				break;
			}
		}
		if(!found) {
			words.push_back(word);
			counts.push_back(1);
		}
	}

	int size = (int) words.size();
	for(int i = 0; i < size; i++)
		cout << words[i] << " " << counts[i] << endl;

	return 0;
}
