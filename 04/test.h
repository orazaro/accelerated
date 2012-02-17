#ifndef GUARD_test_h
#define GUARD_test_h

#include "grade.h"
#include "median.h"


#include <cppunit/extensions/HelperMacros.h>

class myTest : public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void checkGrade() {
        CPPUNIT_ASSERT_MESSAGE("grade_0_0_0", 0 == grade(0,0,0));
        double grade_1_1_1 = 1.0;
        CPPUNIT_ASSERT_EQUAL(grade_1_1_1, grade(1,1,1));
        double grade_1_2_3 = 2.2;
        CPPUNIT_ASSERT_EQUAL(grade_1_2_3, grade(1,2,3));
#ifndef GRADE_INPLACE
        Student_info s; double g;
        {
            double array[] = {93, 91, 47, 90, 92, 73, 100, 87};
            s.midterm = array[0]; s.final = array[1];
            s.homework = 
                std::vector<double>(array+2, array+sizeof(array)/sizeof(double));
            g = 90.4;
            CPPUNIT_ASSERT_EQUAL(g, grade(s));
        }
        {
            double array[] = {75, 90, 86, 92, 93, 60, 1, 98};
            s.midterm = array[0]; s.final = array[1];
            s.homework = 
                std::vector<double>(array+2, array+sizeof(array)/sizeof(double));
            g = 86.6;
            CPPUNIT_ASSERT_EQUAL(g, grade(s));
        }
#endif
    }
    void checkMedian() {
        std::vector<double> vec(5,0);
        double med = 0;
        CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
        vec[0] = 1; med = 0;
        CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
        vec[0] = 1; vec[1] = 2; med = 0;
        CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
        vec[0] = 1; vec[1] = 2; vec[2] = 3; med = 1;
        CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
        double array[] = {2,5,4,3,1}; med = 3.0;
        vec = std::vector<double>(array, array+sizeof(array)/sizeof(double));
        CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
    }
    CPPUNIT_TEST_SUITE( myTest );
    CPPUNIT_TEST( checkGrade );
    CPPUNIT_TEST( checkMedian );
    CPPUNIT_TEST_SUITE_END();
};

#endif /*GUARD_test_h*/
