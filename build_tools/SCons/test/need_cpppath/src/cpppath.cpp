/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "src/cpppath.t.h"

static CppPathTest suite_CppPathTest;

static CxxTest::List Tests_CppPathTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CppPathTest( "src/cpppath.t.h", 17, "CppPathTest", suite_CppPathTest, Tests_CppPathTest );

static class TestDescription_CppPathTest_test_i_need_me_exists : public CxxTest::RealTestDescription {
public:
 TestDescription_CppPathTest_test_i_need_me_exists() : CxxTest::RealTestDescription( Tests_CppPathTest, suiteDescription_CppPathTest, 20, "test_i_need_me_exists" ) {}
 void runTest() { suite_CppPathTest.test_i_need_me_exists(); }
} testDescription_CppPathTest_test_i_need_me_exists;

#include <cxxtest/Root.cpp>
