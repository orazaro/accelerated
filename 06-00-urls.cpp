#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <string>
#include <algorithm>

//#define FAST

std::string::const_iterator
url_beg_my(std::string::const_iterator b, std::string::const_iterator e)
{
    using namespace std;
    typedef string::const_iterator iter;
    const string beg("://");
    
    while(b != e) {
        while(b != e && !isalpha(*b)) ++b;
        iter t = b;
        while(b != e && isalpha(*b)) ++b;
        if(equal(b, b+beg.size(), beg.begin()))
            return t;
    }
    return b;
}
std::string::const_iterator
url_beg_fast(std::string::const_iterator b, std::string::const_iterator e)
{
    typedef enum {
        s_undef,
        s_alpha,
        s_beg1,
        s_beg2,
        s_beg3
    } state;
    using namespace std;
    typedef string::const_iterator iter;
    state s = s_undef;

    iter head = e;
    while(b != e) {
        switch(s){
            case s_undef:
                if(isalpha(*b)) {
                    s = s_alpha;
                    head = b;
                }
                ++b;
            break;
            case s_alpha:
                if(*b == ':')
                    s = s_beg1;
                else if(!isalpha(*b))
                    s = s_undef;
                ++b;
            break;
            case s_beg1:
                if(*b == '/') {
                    s = s_beg2;
                }
                else if(isalpha(*b)) {
                    s = s_alpha;
                    head = b;
                } else
                    s = s_undef;
                ++b;
            break;
            case s_beg2:
                if(*b == '/') {
                    return head;
                }
                else if(isalpha(*b)) {
                    s = s_alpha;
                    head = b;
                } else
                    s = s_undef;
                ++b;
            break;
            default:
            throw runtime_error("bad state!");
            break;
        }
    }
    return e;
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
#ifdef FAST
        b = url_beg_fast(b, e);
#else
        b = url_beg_my(b, e);
#endif
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

#include <time.h>
#include <sys/time.h>
double difftimeofday(const struct timeval *tvStart, const struct timeval *tvEnd)
{
    #define SEC_TO_MKSEC(s) ((s) * 1000 * 1000) 
    size_t t1 = (SEC_TO_MKSEC(tvStart->tv_sec) + tvStart->tv_usec);
    size_t t2 = (SEC_TO_MKSEC(tvEnd->tv_sec) + tvEnd->tv_usec);
    double rdiff = t2 > t1 ? (double)(t2 - t1)/1000. : 0;
    return rdiff;
}    

void myTest::checkResult() 
{
    using namespace std;
    typedef vector<string> vec_str;
    const string dummy1("ftp://www.com/b.b?p1=1&p2=2");
    vec_str vec = find_urls(dummy1);
    CPPUNIT_ASSERT_EQUAL((vec_str::size_type)1, vec.size());
    const string dummy0("www.com/b.b?p1=1&p2=2");
    vec = find_urls(dummy0);
    CPPUNIT_ASSERT_EQUAL((vec_str::size_type)0, vec.size());

    const string dummy2("http://a.com/b/c.d?p1=e&p2=f");
    string input(" \tone two\n");
    input += dummy1 + ">tree\tfour five\t<a href=\"";
    input += dummy2 + "\">link</a>http:aaahtbbhttp:/ddhttp:";
    
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

    /* check speed */
    {
        struct timeval tvStart,tvEnd;
        gettimeofday (&tvStart,NULL);
        cout << "bench start..";
        int n = 10000;
        for(int i = 0; i < n; i++) {
            vec = find_urls(input);
        }    
        cout << "end" << endl;
        gettimeofday (&tvEnd,NULL);
        double dt = difftimeofday(&tvStart, &tvEnd) / n;
        double dtmax = 0.02;
        cout << "dt=" << dt  << " mSec"<< endl;
        CPPUNIT_ASSERT_MESSAGE("bench speed > 0.02 mSec",dt < dtmax);

    }
}

#include "cppunit_run.inc"
