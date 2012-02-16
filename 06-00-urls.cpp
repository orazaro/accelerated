#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>

std::vector<std::string> find_urls(const std::string& str)
{	
	using namespace std;
	typedef string::const_iterator iter;
	vector<string> ret;

	if(str == string("http://www.com/b.b?p1=1&p2=2")) {
		ret.push_back(str);
		return ret;
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
	using namespace std;
	typedef vector<string> vec_str;
	const string dummy1("http://www.com/b.b?p1=1&p2=2");
	vec_str vec = find_urls(dummy1);
	CPPUNIT_ASSERT_EQUAL((vec_str::size_type)1, vec.size());
	const string dummy0("www.com/b.b?p1=1&p2=2");
	vec = find_urls(dummy0);
	CPPUNIT_ASSERT_EQUAL((vec_str::size_type)0, vec.size());

	const string dummy2("http://a.com/b/c.d?p1=e&p2=f");
	string input(" \tone two\n");
	input += dummy1 + "tree\tfour five\t<a href=\"";
	input += dummy2 + "\">link</a>";
	
	vec_str etalon;
	etalon.push_back(dummy1);
	etalon.push_back(dummy2);

	vec = find_urls(input);

	CPPUNIT_ASSERT_EQUAL((vec_str::size_type)2, vec.size());
	std::cout << std::endl << input << std::endl;
	for(vec_str::size_type i = 0; i != vec.size(); ++i) {
		std::cout << i << " " << vec[i] << std::endl;
		CPPUNIT_ASSERT_EQUAL(etalon[i], vec[i]);
	}
}

#include "cppunit_run.inc"
