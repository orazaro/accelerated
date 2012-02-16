#include <iostream>
#include <vector>
#include <stdexcept>

double CalcAverage(const std::vector<double>& vec)
{    
    typedef std::vector<double>::size_type vec_sz;
    double sum = 0;
    for(vec_sz i = 0; i < vec.size(); ++i)
        sum += vec[i];
    return sum / vec.size();
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
    double g = 4.16666666666667;
    double array[] = {1,2,3,4,5,10};
    std::vector<double> vec = std::vector<double>(array, array+sizeof(array)/sizeof(double));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(g, CalcAverage(vec), 0.001);
}

#include "cppunit_run.inc"
