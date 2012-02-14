#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

double grade(double midterm, double final, double homework)
{
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double median(vector<double> vec)
{
	typedef vector<double>::size_type vec_sz;

	vec_sz size = vec.size();
	if(size == 0) 
		throw domain_error("median of an empty vector");
	
	sort(vec.begin(), vec.end());
	vec_sz mid = size / 2;

	return
		size % 2 == 0 ?
		(vec[mid-1] + vec[mid]) / 2 :
		vec[mid];
}

double grade(double midterm, double final, const vector<double>& hw)
{
	if( hw.size() == 0 )
		throw domain_error("student has done no homework");
	return grade(midterm, final, median(hw));
}

istream& read_hw(istream& in, vector<double>& hw)
{
	if(in) {
		// reset vector
		hw.clear();
		double x;
		while( in >> x )
			hw.push_back(x);
		// clear failure flag for istream
		in.clear();
	}
	return in;
}

/* CppUnit tests START */
#include <cppunit/extensions/HelperMacros.h>

class myTest : public CppUnit::TestFixture {
public:
	void setUp() {}
	void tearDown() {}

	void checkGrade() {
		CPPUNIT_ASSERT_MESSAGE("grade_0_0_0", 0 == grade(0,0,0));
		double grade_1_1_1 = 1;
		CPPUNIT_ASSERT_EQUAL(grade_1_1_1, grade(1,1,1));
		double grade_1_2_3 = 2.2;
		CPPUNIT_ASSERT_EQUAL(grade_1_2_3, grade(1,2,3));
	}
	void checkMedian() {
		vector<double> vec(5,0);
		double med = 0;
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
		vec[0] = 1; med = 0;
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
		vec[0] = 1; vec[1] = 2; med = 0;
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
		vec[0] = 1; vec[1] = 2; vec[2] = 3; med = 1;
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
		double array[] = {2,5,4,3,1}; med = 3.0;
		vec = vector<double>(array, array+sizeof(array)/sizeof(double));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bad median", med, median(vec));
	}
	CPPUNIT_TEST_SUITE( myTest );
	CPPUNIT_TEST( checkGrade );
	CPPUNIT_TEST( checkMedian );
	CPPUNIT_TEST_SUITE_END();
};
CPPUNIT_TEST_SUITE_REGISTRATION ( myTest );
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
bool run_all_tests()
{
  CppUnit::Test *test =
    CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextTestRunner runner;
  runner.addTest(test);

  return runner.run();
}
#include <cppunit/TestResult.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TestResultCollector.h>
bool run_all_tests_xml()
{
	CppUnit::TestResult    controller;
	CppUnit::TestResultCollector result;
	controller.addListener(&result);

  CppUnit::Test *test =
    CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextTestRunner runner;
  runner.addTest(test);

  runner.run(controller);
	ofstream xmlFileOut("cpptestresults.xml");
	CppUnit::XmlOutputter xmlOut(&result, xmlFileOut);
	xmlOut.write();

	return result.testFailuresTotal() == 0;
}
/* CppUnit tests END */

int main()
{
	if(!run_all_tests()) {
		std::cerr << "bad test result: exit" << endl;
		return 1;
	}
	cout << "Please, enter your name: ";
	string name;
	cin >> name;
	cout << "Hello, " << name << "!" << endl;

	cout << "Please enter your midterm and final exam grades: ";
	double midterm, final;
	cin >> midterm >> final;

	cout << "Enter all your homework grades, "
		"followed by end-of-file: ";

	vector<double> homework;

	read_hw(cin, homework);

	try {
		double final_grade = grade(midterm, final, homework);
		streamsize prec = cout.precision();
		cout << "Your final grade is " << setprecision(3)
			<< final_grade << setprecision(prec) << endl;
	} catch (domain_error) {
		cout << endl << "You must enter your grades. "
			"Please try again" << endl;
		return 1;
	}
	return 0;
}

