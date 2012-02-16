/* RUN TESTS */

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
static bool run_all_tests()
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
static const char* cpptestresults = "cpptestresults.xml";

static bool run_all_tests_xml()
{
	CppUnit::TestResult    controller;
	CppUnit::TestResultCollector result;
	controller.addListener(&result);

  CppUnit::Test *test =
    CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextTestRunner runner;
  runner.addTest(test);

  runner.run(controller);
	std::ofstream xmlFileOut(cpptestresults);
	CppUnit::XmlOutputter xmlOut(&result, xmlFileOut);
	xmlOut.write();

	return result.testFailuresTotal() == 0;
}

int main(int argc, char* argv[])
{
	bool res;
	if(argc > 1 && (std::string(argv[1]) == std::string("xml")) ) {
		res = run_all_tests_xml();
        std::cerr << "xml output saved: " << cpptestresults << std::endl;
    }
	else
		res = run_all_tests();

	return res?0:1;
}

