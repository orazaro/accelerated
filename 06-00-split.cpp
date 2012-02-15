#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>

bool space(char c)
{
	return isspace(c);
}
bool not_space(char c)
{
	return !isspace(c);
}

std::vector<std::string> split(const std::string& str)
{	
	using namespace std;
	typedef string::const_iterator iter;
	vector<string> ret;

	iter i = str.begin();
	while(i != str.end())
	{
		// ignore leading spaces
		i = find_if(i, str.end(), not_space);
		// find end of next word
		iter j = find_if(i, str.end(), space);
		if(i != str.end())
			ret.push_back(string(i, j));
		i = j;
	}
	return ret;
}

/* SETUP TESTS */

#include <cppunit/extensions/HelperMacros.h>
class myTest : public CppUnit::TestFixture {
public:
	void setUp() {}
	void tearDown() {}

	void checkResult();
	CPPUNIT_TEST_SUITE( myTest );
	CPPUNIT_TEST( checkResult );
	CPPUNIT_TEST_SUITE_END();
};
CPPUNIT_TEST_SUITE_REGISTRATION ( myTest );
	
void myTest::checkResult() 
{
	typedef std::vector<std::string> vec_str;
	
	vec_str vec = split(std::string(""));
	CPPUNIT_ASSERT_EQUAL((vec_str::size_type)0, vec.size());
	vec = split(std::string("test"));
	CPPUNIT_ASSERT_EQUAL((vec_str::size_type)1, vec.size());

	const std::string input(" \tone two\n    tree\tfour five\t\t");
	vec_str etalon;
	etalon.push_back("one");
	etalon.push_back("two");
	etalon.push_back("tree");
	etalon.push_back("four");
	etalon.push_back("five");

	vec = split(input);

	CPPUNIT_ASSERT_EQUAL((vec_str::size_type)5, vec.size());
	std::cout << std::endl << input << std::endl;
	for(vec_str::size_type i = 0; i != vec.size(); ++i) {
		std::cout << i << " " << vec[i] << std::endl;
		CPPUNIT_ASSERT_EQUAL(etalon[i], vec[i]);
	}
}

#include "cppunit_run.inc"
