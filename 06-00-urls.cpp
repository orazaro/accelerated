#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <string>
#include <algorithm>

std::string::const_iterator
url_beg(std::string::const_iterator b, std::string::const_iterator e)
{
}


bool not_url_char(char c)
{
    static const std::string url_ch = "~;/?:@=&$-_.+!*'(),";
    return !( 
        isalnum(c) ||
        find(url_ch.begin(), url_ch.end(), c) != url_ch.end()
        );
}

std::string::const_iterator
url_end(std::string::const_iterator b, std::string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

std::vector<std::string> find_urls(const std::string& s)
{    
    using namespace std;
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();
    
    // look through the entire input
    while(b != e) {
        // look for one or more letters followed by ://
        b = url_beg(b, e);
        // if we found it
        if(b != e) {
            // get the rest of the URL
            iter after = url_end(b, e);

            ret.push_back(string(b, after));
            b = after;
        }
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
