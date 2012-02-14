#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

typedef std::list<std::string> wordlist;

wordlist split(const std::string& s)
{	
	wordlist words; 
	std::string::const_iterator i = s.begin();
	while(i != s.end())
	{
		while(i != s.end() && isspace(*i))
			++i; 
		std::string::const_iterator j = i;
		while(j != s.end() && !isspace(*j))
			++j;
		if(j != i) {
			words.push_back(std::string(i, j));
			i = j;
		}
	}

	return words;
}

std::string::size_type width(const wordlist& v)
{
	string::size_type maxlen = 0;
	for(wordlist::const_iterator iter = v.begin();
		iter != v.end(); ++iter)
		maxlen = max(maxlen, iter->size());
	return maxlen;
}

std::vector<std::string> hcat(const std::vector<std::string>& left,
	const std::vector<std::string>& right)
{
	vector<string> ret;
	string::size_type w1 = 36, w2 = 38, dw = 3;
	vector<string>::size_type i = 0, j = 0;

	while(i != left.size() || j != right.size())
	{
		string s;
		if(i != left.size()) {
			string s2 = left[i++];
			if(s2.size() >= w1) {
				s = s2.substr(s2.size() - w1, w1);
			} else {
				s = string(w1 - s2.size(),' ') + s2;
			}
			s += string(dw, ' ');
		} else {
			s = string(w1 + dw, ' ');
		}
		if(j != right.size()) {
			string s2 = right[j++];
			if(s2.size() >= w2) {
				s += s2.substr(0, w2);
			} else {
				s += s2;
				s += string(w2 - s2.size(),' ');
			}
		}
		ret.push_back(s);
	}

	return ret;
}

void out(const std::vector<std::string>& v)
{
	for(std::vector<std::string>::const_iterator iter = v.begin();
		iter != v.end(); ++iter)
		cout << *iter << endl;
}

const string endmark("<ENDMARK>");
const string sepmark("<SEPMARK>");

void rotate(wordlist& rot, bool left = true)
{
	if(left) {
		rot.push_back(*rot.begin());
		rot.erase(rot.begin());
	} else {
		rot.insert(rot.begin(), *rot.rbegin());
		rot.pop_back();
	}
}

string merge(const wordlist& vec)
{
	if(!vec.size()) return string("");
	wordlist::const_iterator it = vec.begin();
	string m = *it;
	for(++it; it != vec.end(); ++it) {
		m += " " + *it;
	}
	return m;
}

void read(vector<string>& rot, const string& str)
{
	/*convert*/
	string s = str;
	for(string::size_type i = 0; i != str.size(); ++i) {
		if(isalnum(str[i]))
			s[i] = tolower(str[i]);
		else
			s[i] = ' ';
	}

	wordlist vec = split(s);
	int n = (int)vec.size();
	vec.push_back(endmark);
	for(int i = 0; i < n; ++i) {
		rot.push_back(merge(vec));
		rotate(vec);
	}
}
int main(int argc, char* argv[])
{
	vector<string> rot;

	if(argc > 1 && string(argv[1]) == string("test")) {
		read(rot, "The quick brown fox");
		read(rot, "jumped over the fence ogogo");
	}
	else {
		string s;
		while(getline(cin, s))
			read(rot, s);
	}

	sort(rot.begin(), rot.end());

	vector<string> left, right, ret;
	for(vector<string>::iterator it = rot.begin();
		it != rot.end(); ++it) 
	{
		wordlist vec = split(*it);
		vec.insert(vec.begin(), sepmark);
		while(*(vec.rbegin()) != endmark)
			rotate(vec, false);
		wordlist l, r;
		wordlist::const_iterator i = vec.begin(), j = i;
		while(*j != sepmark) ++j;
		l = wordlist(i,j);
		++j; i = j;
		while(*j != endmark) ++j;
		r = wordlist(i,j);
		left.push_back(merge(l));
		right.push_back(merge(r));
	}

	ret = hcat(left, right);
	out(ret);

	return 0;
}


