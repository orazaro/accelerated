#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <string>
#include <algorithm>

bool not_url_char(char c)
{
    static const std::string url_ch = "~;/?:@=&$-_.+!*'(),";
    return !( 
        isalnum(c) ||
        find(url_ch.begin(), url_ch.end(), c) != url_ch.end()
        );
}

/*** variations of url_beg ***/
// fast enought because of search
std::string::const_iterator
url_beg_book(std::string::const_iterator b, std::string::const_iterator e)
{
    using namespace std;
    static const string sep = "://";
    typedef string::const_iterator iter;

    iter i = b;
    while((i = search(i, e, sep.begin(), sep.end())) != e) {
        //make sure the separator isn't at the beginning or end of the line
        if(i != b && i + sep.size() != e) {
            iter beg = i;
            while(beg != b && isalpha(beg[-1]))
                --beg;
            // is there at least one appropriate character 
            // before and after the separator?
            if(beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }
        i += sep.size();
    }
    return e;
}
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
/* url_beg_fast add +20% speed */
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
/*** variations of url_beg END ***/

std::string::const_iterator
url_end(std::string::const_iterator b, std::string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

static std::string::const_iterator
(&url_beg_ref)(std::string::const_iterator, std::string::const_iterator)
= url_beg_book; /* variants: _book, _my, _fast */

std::vector<std::string> find_urls(const std::string& s)
{    
    using namespace std;
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();

    // look through the entire input
    while(b != e) {
        // look for one or more letters followed by ://
        b = url_beg_ref(b, e);
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
    void setUp() {
        using namespace std;
        typedef vector<string> vec_str;
        m_dummy1 = string("ftp://www.com/b.b?p1=1&p2=2");
        m_dummy0 = string("www.com/b.b?p1=1&p2=2");
        m_dummy2 = string("http://a.com/b/c.d?p1=e&p2=f");
        m_input = string(" \tone two\n");
        m_input += m_dummy1 + ">tree\tfour five\t<a href=\"";
        m_input += m_dummy2 + "\">link</a>http:aaahtbbhttp:/ddhttp:";
    }
    void tearDown() {}

    void checkResult();
    void checkSpeed();
    CPPUNIT_TEST_SUITE( myTest );
    CPPUNIT_TEST( checkResult );
    CPPUNIT_TEST( checkSpeed );
    CPPUNIT_TEST_SUITE_END();

    std::string m_dummy0;
    std::string m_dummy1;
    std::string m_dummy2;
    std::string m_input;
};
CPPUNIT_TEST_SUITE_REGISTRATION ( myTest );

void myTest::checkResult() 
{
    using namespace std;
    typedef vector<string> vec_str;
    vec_str vec = find_urls(m_dummy1);
    CPPUNIT_ASSERT_EQUAL((vec_str::size_type)1, vec.size());
    vec = find_urls(m_dummy0);
    CPPUNIT_ASSERT_EQUAL((vec_str::size_type)0, vec.size());

    vec_str etalon;
    etalon.push_back(m_dummy1);
    etalon.push_back(m_dummy2);

    vec = find_urls(m_input);

    CPPUNIT_ASSERT_EQUAL((vec_str::size_type)2, vec.size());
    std::cout << std::endl << m_input << std::endl;
    for(vec_str::size_type i = 0; i != vec.size(); ++i) {
        std::cout << i << " " << vec[i] << std::endl;
        CPPUNIT_ASSERT_EQUAL(etalon[i], vec[i]);
    }
}

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

void myTest::checkSpeed() 
{
    using namespace std;
    std::vector<std::string> vec;
    
    struct timeval tvStart,tvEnd;
    gettimeofday (&tvStart,NULL);
    cout << "bench start..";
    int n = 10000;
    for(int i = 0; i < n; i++) {
        vec = find_urls(m_input);
    }    
    cout << "end" << endl;
    gettimeofday (&tvEnd,NULL);
    double dt = difftimeofday(&tvStart, &tvEnd) / n;
    double dtmax = 0.02;
    cout << "dt=" << dt  << " mSec"<< endl;
    CPPUNIT_ASSERT_MESSAGE("bench speed > 0.02 mSec",dt < dtmax);
}

#include "cppunit_run.inc"
