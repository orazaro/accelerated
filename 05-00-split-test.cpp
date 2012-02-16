#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>

#if 1
std::vector<std::string> split(const std::string& s)
{    
    std::vector<std::string> vec; 
    std::string::const_iterator i = s.begin();
    while(i != s.end())
    {
        while(i != s.end() && isspace(*i))
            ++i; 
        std::string::const_iterator j = i;
        while(j != s.end() && !isspace(*j))
            ++j;
        if(j != i) {
            std::string token = std::string(i, j);
            vec.push_back(token);
            i = j;
        }
    }

    return vec;
}
#else
std::vector<std::string> split(const std::string& s)
{    
    std::vector<std::string> vec; 
    typedef std::string::size_type string_size;
    string_size i = 0;
    while(i != s.size())
    {
        while(i != s.size() && isspace(s[i]))
            ++i; 
        string_size j = i;
        while(j != s.size() && !isspace(s[j]))
            ++j;
        if(j != i) {
            std::string token = s.substr(i, j-i);
            vec.push_back(token);
            i = j;
        }
    }

    return vec;
}
#endif

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
