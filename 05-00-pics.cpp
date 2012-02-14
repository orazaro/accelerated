#include <iostream>
#include <string>
#include <vector>

using namespace std;

void out(const std::vector<std::string>& v)
{
	for(std::vector<std::string>::const_iterator iter = v.begin();
		iter != v.end(); ++iter)
		cout << *iter << endl;
}

std::string::size_type width(const std::vector<std::string>& v)
{
	string::size_type maxlen = 0;
	for(std::vector<std::string>::const_iterator iter = v.begin();
		iter != v.end(); ++iter)
		maxlen = max(maxlen, iter->size());
	return maxlen;
}

std::vector<std::string> frame(const std::vector<std::string>& v)
{
	vector<string> ret;
	string::size_type maxlen = width(v);
	string border(maxlen + 4, '*');
	ret.push_back(border);
	for(std::vector<std::string>::const_iterator iter = v.begin();
		iter != v.end(); ++iter) {
		ret.push_back("* " + (*iter) + string(maxlen - iter->size(),' ') + " *");
	}
	ret.push_back(border);
	return ret;
}

std::vector<std::string> vcat(const std::vector<std::string>& top,
	const std::vector<std::string>& bottom)
{
	vector<string> ret = top;
#if 0
	for(std::vector<std::string>::const_iterator it = bottom.begin();
		it != bottom.end(); ++it) {
		ret.push_back(*it);
	}
#else
	ret.insert(ret.end(),bottom.begin(),bottom.end());
#endif
	return ret;
}

std::vector<std::string> hcat(const std::vector<std::string>& left,
	const std::vector<std::string>& right)
{
	vector<string> ret;
	string::size_type width1 = width(left) + 1;
	vector<string>::size_type i = 0, j = 0;

	while(i != left.size() || j != right.size())
	{
		string s;
		if(i != left.size())
			s = left[i++];
		s += string(width1 - s.size(),' ');
		if(j != right.size())
			s += right[j++];
		ret.push_back(s);
	}

	return ret;
}

int main()
{
	// read data
	vector<string> v,f;
	string line;
	while(getline(cin, line))
		v.push_back(line);
	f = frame(v);
	out(vcat(v,f));
	out(hcat(v,f));
}
