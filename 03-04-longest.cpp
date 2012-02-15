#include <iostream>
#include <string>

using namespace std;

int main()
{
	string strmin, strmax, word;
	string::size_type lenmin,lenmax;

	cin >> word;
	strmin = strmax = word;
	lenmin = lenmax = word.size();

	while(cin >> word)
	{
		string::size_type  len = word.size();
		if(len > lenmax) {
			lenmax = len;
			strmax = word;
		}
		if(len < lenmin) {
			lenmin = len;
			strmin = word;
		}
	}

	cout << "longest: " << strmax << " [" << lenmax << "]" << endl;
	cout << "shortest: " << strmin << " [" << lenmin << "]" << endl;

	return 0;
}
